#include <algorithm>
#include "workflow.h"

void Workflow::execute(const std::string &configFileName) {
    commands.clear();
    workOrder.clear();

    std::string str;
    std::ifstream input(configFileName);
    getline(input, str);
    if(str.empty()) {
        throw FileNotFoundException("config file not found\n");
    }
    if(str != "desc") {
        throw ConfigFileFormatException("\"desc\" header not found\n");
    }

    for(getline(input, str); str != "csed" && !str.empty(); getline(input, str)) {
        auto firstSpacePos = str.find(' '),
            secondSpacePos = str.find(' ', firstSpacePos + 1);
        if(firstSpacePos == std::string::npos || secondSpacePos == std::string::npos) {
            throw ConfigFileFormatException("too few data for command\n");
        }
        if(str.at(firstSpacePos + 1) != '=') {
            throw ConfigFileFormatException("expected operator \"=\"\n");
        }
        char *chr;
        int id = (int) std::strtol(str.c_str(), &chr, 10);
        std::string instruction = str.substr(secondSpacePos + 1);
        if(*chr != ' ') {
            throw ConfigFileFormatException("failed to bind id to int\n");
        }
        if(commands.count(id) != 0) {
            throw ConfigFileFormatException("redefinition of id=" + std::to_string(id) + "\n");
        }
        Worker *worker = WorkerFactory::instance().createWorker(instruction);

        commands.emplace(std::make_pair(id, worker));
    }
    if(str.empty()) {
        throw ConfigFileFormatException("\"csed\" footer not found\n");
    }

    int num;
    input >> num;
    if(input.eof()) {
        throw ConfigFileFormatException("work order not found\n");
    }
    if(input.fail()) {
        throw ConfigFileFormatException("couldn't bind to int\n");
    }
    workOrder.push_back(num);

    for(;;) {
        getline(input, str, ' ');
        getline(input, str, ' ');
        if(input.eof()) {
            if(!str.empty() && str != "\n") {
                throw ConfigFileFormatException("garbage at the end\n");
            }
            break;
        }
        if(str != "->") {
            throw ConfigFileFormatException("expected operator \"->\"\n");
        }

        input >> num;
        if(input.eof()) {
            throw ConfigFileFormatException("id not found\n");
        }
        if(input.fail()) {
            throw ConfigFileFormatException("couldn't bind to int\n");
        }
        workOrder.push_back(num);
    }
    input.close();

    int pos = 0;
    for(auto &iter: workOrder) {
        Worker *worker;
        try {
            worker = commands.at(iter).get();
        }
        catch(std::out_of_range &err) {
            throw ConfigFileFormatException("id " + std::to_string(iter) + " not found\n");
        }
        if((pos == 0) != (worker->name() == "FileReader")) {
            throw CommandCompatibilityException("wrong place for readfile, pos " + std::to_string(pos) + " \n");
        }
        if((pos == workOrder.size() - 1) != (worker->name() == "FileWriter")) {
            throw CommandCompatibilityException("wrong place for writefile, pos " + std::to_string(pos) + " \n");
        }
        pos++;
    }

    for(int index : workOrder) {
        commands[index]->run(buffer);
    }
}
