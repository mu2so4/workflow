#ifndef WORKFLOW_BLOCKS_H
#define WORKFLOW_BLOCKS_H

#include "worker.h"

class FileReader: public Worker {
    std::string inputFile;
public:
    explicit FileReader(std::string filename):
            inputFile(std::move(filename)) {}

    std::string name() override;
    void run(std::vector<std::string> &buffer) const override;
};

class FileDumper: public Worker {
    std::string outputFile;
public:
    explicit FileDumper(std::string filename):
            outputFile(std::move(filename)) {}

    std::string name() override;
    void run(std::vector<std::string> &buffer) const override;
};

class FileWriter: public Worker {
    std::string outputFile;
public:
    explicit FileWriter(std::string filename):
            outputFile(std::move(filename)) {}

    std::string name() override;
    void run(std::vector<std::string> &buffer) const override;
};

class Sorter: public Worker {
public:
    std::string name() override;
    void run(std::vector<std::string> &buffer) const override;
};

class Grepper: public Worker {
    std::string condition;
public:
    explicit Grepper(std::string cond):
            condition(std::move(cond)) {}

    std::string name() override;
    void run(std::vector<std::string> &buffer) const override;
};

class Replacer: public Worker {
    std::string oldWord;
    std::string newWord;
public:
    Replacer(std::string from, std::string to):
            oldWord(std::move(from)),
            newWord(std::move(to)) {}

    std::string name() override;
    void run(std::vector<std::string> &buffer) const override;
};

#endif //WORKFLOW_BLOCKS_H
