#include "blocks.h"

#include <algorithm>
#include <fstream>
#include "dynamic_array.h"


void FileReader::run(const std::string &params, Buffer &buffer) const {
    if(buffer.isLoaded) {
        throw IllegalStateException("attempt to read one more file\n");
    }
    unsigned long long spaces[2];
    spaces[0] = params.find(' ');
    spaces[1] = params.find(' ', spaces[0] + 1);

    if(params.substr(0, spaces[0]) != "readfile") {
        throw ArgumentException("attempt to do something else, not reading\n");
    }
    if(spaces[0] == std::string::npos) {
        throw ArgumentException("too few arguments for reading\n");
    }
    if(spaces[1] != std::string::npos) {
        throw ArgumentException("too many arguments for reading\n");
    }

    std::string filename = params.substr(spaces[0] + 1);

    std::ifstream input(filename);
    if(!input.is_open()) {
        throw FileNotFoundException(filename + " not found\n");
    }

    DynamicArray<std::string> data;
    for(;;) {
        std::string str;
        getline(input, str);
        if(input.eof())
            break;
        data.pushBack(str);
    }
    input.close();
    std::pair<std::string*, int> res = data.exportData();
    buffer.loadData(res.first, res.second);
    res.first = nullptr;
    buffer.isLoaded = true;
}

void FileDumper::run(const std::string &params, Buffer &buffer) const {
    if(!buffer.isLoaded) {
        throw IllegalStateException("attempt to dump before file reading\n");
    }
    if(buffer.isSaved) {
        throw IllegalStateException("attempt to dump after file writing\n");
    }
    if(buffer.isDumped) {
        throw IllegalStateException("attempt to do one more dumping\n");
    }

    unsigned long long spaces[2];
    spaces[0] = params.find(' ');
    spaces[1] = params.find(' ', spaces[0] + 1);

    if(params.substr(0, spaces[0]) != "dump") {
        throw ArgumentException("attempt to do something else, not dumping\n");
    }
    if(spaces[0] == std::string::npos) {
        throw ArgumentException("too few arguments for dumping\n");
    }
    if(spaces[1] != std::string::npos) {
        throw ArgumentException("too many arguments for dumping\n");
    }

    std::string filename = params.substr(spaces[0] + 1);
    std::ofstream output(filename);

    for(int index = 0; index < buffer.size; index++) {
        output << buffer.data[index] << '\n';
    }
    buffer.isDumped = true;
}

void FileWriter::run(const std::string &params, Buffer &buffer) const {
    if(!buffer.isLoaded) {
        throw IllegalStateException("attempt to write before file reading\n");
    }
    if(buffer.isSaved) {
        throw IllegalStateException("attempt to write one more file\n");
    }
    unsigned long long spaces[2];
    spaces[0] = params.find(' ');
    spaces[1] = params.find(' ', spaces[0] + 1);

    if(params.substr(0, spaces[0]) != "writefile") {
        throw ArgumentException("attempt to do something else, not writing\n");
    }
    if(spaces[0] == std::string::npos) {
        throw ArgumentException("too few arguments for writing\n");
    }
    if(spaces[1] != std::string::npos) {
        throw ArgumentException("too many arguments for writing\n");
    }

    std::string filename = params.substr(spaces[0] + 1);
    std::ofstream output(filename);

    for(int index = 0; index < buffer.size; index++) {
        output << buffer.data[index] << '\n';
    }
    buffer.clear();
    buffer.isSaved = true;
}


void Sorter::run(const std::string &params, Buffer &buffer) const {
    if(!buffer.isLoaded) {
        throw IllegalStateException("attempt to sort before file reading\n");
    }
    if(buffer.isSaved) {
        throw IllegalStateException("attempt to sort after file writing\n");
    }
    if(params != "sort") {
        throw ArgumentException("sort command has no arguments\n");
    }
    std::sort(buffer.data, buffer.data + buffer.size);
}


void Grepper::run(const std::string &params, Buffer &buffer) const {
    if(!buffer.isLoaded) {
        throw IllegalStateException("attempt to grep before file reading\n");
    }
    if(buffer.isSaved) {
        throw IllegalStateException("attempt to grep after file writing\n");
    }
    unsigned long long spaces[2];
    spaces[0] = params.find(' ');
    spaces[1] = params.find(' ', spaces[0] + 1);

    if(params.substr(0, spaces[0]) != "grep") {
        throw ArgumentException("attempt to do something else, not grep\n");
    }
    if(spaces[0] == std::string::npos) {
        throw ArgumentException("too few arguments for grep\n");
    }
    if(spaces[1] != std::string::npos) {
        throw ArgumentException("too many arguments for grep\n");
    }

    std::string target = params.substr(spaces[0] + 1, spaces[1] - spaces[0] - 1);
    DynamicArray<std::string> grepping{};

    for(int index = 0; index < buffer.size; index++) {
        if(buffer.data[index].find(target) != std::string::npos)
            grepping.pushBack(buffer.data[index]);
    }
    std::pair<std::string*, int> res = grepping.exportData();
    buffer.loadData(res.first, res.second);
    res.first = nullptr;
}


void Replacer::run(const std::string &params, Buffer &buffer) const {
    if(!buffer.isLoaded) {
        throw IllegalStateException("attempt to replace before file reading\n");
    }
    if(buffer.isSaved) {
        throw IllegalStateException("attempt to replace after file writing\n");
    }
    unsigned long long spaces[3];
    spaces[0] = params.find(' ');
    spaces[1] = params.find(' ', spaces[0] + 1);
    spaces[2] = params.find(' ', spaces[1] + 1);

    if(params.substr(0, spaces[0]) != "replace") {
        throw ArgumentException("attempt to do something else, not replacement\n");
    }
    if(spaces[0] == std::string::npos || spaces[1] == std::string::npos) {
        throw ArgumentException("too few arguments for replacement\n");
    }
    if(spaces[2] != std::string::npos) {
        throw ArgumentException("too many arguments for replacement\n");
    }

    std::string from = params.substr(spaces[0] + 1, spaces[1] - spaces[0] - 1);
    std::string to = params.substr(spaces[1] + 1);

    for(int index = 0; index < buffer.size; index++) {

        for(unsigned long long pos = buffer.data[index].find(from); pos != std::string::npos;
        pos = buffer.data[index].find(from, pos)) {
            buffer.data[index].replace(pos, spaces[1] - spaces[0] - 1, to);
        }
        //if(buffer.data[index] == from)
        //    buffer.data[index] = to;
    }
}