#include "blocks.h"

#include <algorithm>
#include <fstream>

std::string FileReader::name() {
    return "FileReader";
}

void FileReader::run(std::vector<std::string> &buffer) const {
    std::ifstream input(inputFile);

    for(;;) {
        std::string str;
        getline(input, str);
        if(input.eof())
            break;
        buffer.push_back(str);
    }
    input.close();
}

std::string FileDumper::name() {
    return "FileDumper";
}

void FileDumper::run(std::vector<std::string> &buffer) const {
    std::ofstream output(outputFile);

    for(auto &item: buffer) {
        output << item << '\n';
    }
    output.close();
}

std::string FileWriter::name() {
    return "FileWriter";
}

void FileWriter::run(std::vector<std::string> &buffer) const {
    std::ofstream output(outputFile);

    for(auto &item: buffer) {
        output << item << '\n';
    }
    output.close();
    buffer.clear();
}

std::string Sorter::name() {
    return "Sorter";
}


void Sorter::run(std::vector<std::string> &buffer) const {
    std::sort(buffer.begin(), buffer.end());
}

std::string Grepper::name() {
    return "Grepper";
}


void Grepper::run(std::vector<std::string> &buffer) const {
    std::vector<std::string> res;
    for(auto &iter: buffer) {
        if(iter.find(condition) != std::string::npos)
            res.push_back(iter);
    }
    buffer = std::move(res);
}

std::string Replacer::name() {
    return "Replacer";
}


void Replacer::run(std::vector<std::string> &buffer) const {
    auto len1 = oldWord.length(), len2 = newWord.length();
    for(auto &iter: buffer) {
        for(auto pos = iter.find(oldWord); pos != std::string::npos; pos = iter.find(oldWord, pos + len2))
            iter.replace(pos, len1, newWord);
    }
}