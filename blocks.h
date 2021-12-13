#ifndef WORKFLOW_BLOCKS_H
#define WORKFLOW_BLOCKS_H

#include "worker.h"

class FileReader: public Worker {
public:
    void run(const std::string &params, Buffer &buffer) const override;
};

class FileDumper: public Worker {
public:
    void run(const std::string &params, Buffer &buffer) const override;
};

class FileWriter: public Worker {
public:
    void run(const std::string &params, Buffer &buffer) const override;
};

class Sorter: public Worker {
public:
    void run(const std::string &params, Buffer &buffer) const override;
};

class Grepper: public Worker {
public:
    void run(const std::string &params, Buffer &buffer) const override;
};

class Replacer: public Worker {
public:
    void run(const std::string &params, Buffer &buffer) const override;
};

#endif //WORKFLOW_BLOCKS_H
