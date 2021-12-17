#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H

#include <string>
#include <fstream>
#include <vector>
#include "block_creators.h"
#include "factory.h"
#include <map>
#include "exceptions.h"
#include "worker.h"

class Workflow {

    std::map<int, Worker*> commands;
    std::vector<int> workOrder;
    std::vector<std::string> buffer;
    bool isInitiated = false;

public:
    Workflow() = default;
    ~Workflow();

public:
    void work();
    void init(const std::string &filename);
};

#endif //WORKFLOW_WORKFLOW_H
