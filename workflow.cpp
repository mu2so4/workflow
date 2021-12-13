#include "workflow.h"

void Workflow::init(const std::string &configFileName) {
    buffer.isSaved = buffer.isLoaded = buffer.isDumped = false;
    std::string str;
    std::ifstream input(configFileName);
    getline(input, str);
    if(str.empty()) {
        throw FileNotFoundException("config file not found\n");
    }
    if(str != "desc") {
        throw ConfigFileFormatException("\"desc\" header not found\n");
    }
    auto *cmd = new DynamicArray<Command>{};
    for(getline(input, str); str != "csed" && !str.empty(); getline(input, str)) {
        size_t spaces[3];
        spaces[0] = str.find(' ');
        spaces[1] = str.find(' ', spaces[0] + 1);
        spaces[2] = str.find(' ', spaces[1] + 1);
        if(spaces[0] == std::string::npos || spaces[1] == std::string::npos) {
            delete cmd;
            throw ConfigFileFormatException("too few data for command\n");
        }
        if(str.substr(spaces[0] + 1, spaces[1] - spaces[0] - 1) != "=") {
            delete cmd;
            throw ConfigFileFormatException("expected operator \"=\"\n");
        }

        char *chr;
        int id = (int) std::strtol(str.c_str(), &chr, 10);
        std::string instruction = str.substr(spaces[1] + 1);
        if(*chr != ' ') {
            delete cmd;
            throw ConfigFileFormatException("failed to bind id to int\n");
        }
        std::string inst = str.substr(spaces[1] + 1, spaces[2] - spaces[1] - 1);

        AbstractFactory *creator = nullptr;
        if(inst == "readfile")
            creator = new ReaderCreator();
        else if(inst == "writefile")
            creator = new WriterCreator();
        else if(inst == "dump")
            creator = new DumperCreator();
        else if(inst == "sort")
            creator = new SorterCreator();
        else if(inst == "replace")
            creator = new ReplacerCreator();
        else if(inst == "grep")
            creator = new GrepCreator();
        else {
            delete cmd;
            throw ConfigFileFormatException("unexpected command " + inst + "\n");
        }

        Command temp;
        temp = Command{id, instruction, creator->createWorker()};
        cmd->pushBack(temp);
        temp.worker = nullptr;
        delete creator;
    }
    if(str.empty()) {
        delete cmd;
        throw ConfigFileFormatException("\"csed\" footer not found\n");
    }
    std::pair<Command*, int> command = cmd->exportData();
    delete cmd;
    commands = command.first;
    command.first = nullptr;
    commandsCount = command.second;

    auto *works = new DynamicArray<int>{};
    int num;
    input >> num;
    if(input.eof()) {
        delete works;
        delete[] commands;
        throw ConfigFileFormatException("work order not found\n");
    }
    if(input.fail()) {
        delete works;
        delete[] commands;
        throw ConfigFileFormatException("couldn't bind to int\n");
    }
    works->pushBack(num);

    for(;;) {
        getline(input, str, ' ');
        getline(input, str, ' ');
        if(input.eof()) {
            if(!str.empty() && str != "\n") {
                delete works;
                delete[] commands;
                throw ConfigFileFormatException("garbage at the end\n");
            }
            break;
        }
        if(str != "->") {
            delete works;
            delete[] commands;
            throw ConfigFileFormatException("expected operator \"->\"\n");
        }

        input >> num;
        if(input.eof()) {
            delete works;
            delete[] commands;
            throw ConfigFileFormatException("id not found\n");
        }
        if(input.fail()) {
            delete works;
            delete[] commands;
            throw ConfigFileFormatException("couldn't bind to int\n");
        }
        works->pushBack(num);
    }

    input.close();
    std::pair<int*, int> res = works->exportData();
    delete works;
    workOrder = res.first;
    res.first = nullptr;
    workCount = res.second;
    isInitiated = true;

    /*
    std::sort(commands, commands + commandsCount);
    for(int index = 0; index < commandsCount - 1; index++) {
        if(commands[index].id == commands[index + 1].id) {
            int notId = commands[index].id;
            delete[] commands;
            delete[] workOrder;
            throw ConfigFileFormatException(
                    "two and more occurrences of id " + std::to_string(notId) + "\n");
        }
    }
     */
}

Workflow::~Workflow() {
    delete[] commands;
    delete[] workOrder;
}

void Workflow::runBlock(int id) {
    int pos = -1;
    for(int index = 0; index < commandsCount; index++) {
        if(commands[index].id == id) {
            pos = index;
            break;
        }
    }
    if(pos == -1) {
        throw CommandNotFoundException("id " + std::to_string(id) + " not found\n");
    }

    commands[pos].worker->run(commands[pos].instruction, buffer);
}


void Workflow::work() {
    if(!isInitiated) {
        throw IllegalStateException("attempt to work() without init");
    }
    for(int index = 0; index < workCount; index++) {
        runBlock(workOrder[index]);
    }
    if(!buffer.isSaved) {
        delete[] buffer.data;
        buffer.data = nullptr;
        throw ConfigFileFormatException("filewrite missed\n");
    }
    isInitiated = false;
}




Workflow::Command &Workflow::Command::operator=(const Workflow::Command &otherCmd) {
    if(&otherCmd != this) {
        delete worker;
        worker = otherCmd.worker;
        instruction = otherCmd.instruction;
        id = otherCmd.id;
    }
    return *this;
}

Workflow::Command &Workflow::Command::operator=(Workflow::Command &&otherCmd) noexcept {
    if(&otherCmd != this) {
        delete worker;
        worker = otherCmd.worker;
        otherCmd.worker = nullptr;
        instruction = otherCmd.instruction;
        id = otherCmd.id;
    }
    return *this;
}

