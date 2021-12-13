#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H

#include <string>
#include <fstream>
#include "block_creators.h"
#include "dynamic_array.h"
#include "exceptions.h"
#include "buffer.h"
#include "worker.h"

class Workflow {
    struct Command {
        int id = 0;
        std::string instruction;
        Worker *worker = nullptr;

        Command() = default;

        Command(int pos, std::string &command, Worker *workerPtr):
        id(pos),
        instruction(command),
        worker(workerPtr) {}

        Command &operator=(const Command &otherCmd);

        Command &operator=(Command &&otherCmd) noexcept;

        ~Command() {
            delete worker;
        }
    };

    Command *commands = nullptr;
    int commandsCount;
    int *workOrder = nullptr;
    int workCount;
    Buffer buffer;

public:
    explicit Workflow(const std::string &configFileName);
    ~Workflow();

private:
    void runBlock(int id);

public:
    void work();
};

#endif //WORKFLOW_WORKFLOW_H
