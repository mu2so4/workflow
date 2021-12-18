#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H

#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include "factory.h"

class Workflow {

    std::map<int, std::unique_ptr<Worker>> commands;
    std::vector<int> workOrder;
    std::vector<std::string> buffer;

public:
    Workflow() = default;
    ~Workflow() = default;

public:
    void execute(const std::string &configFileName);
};

#endif //WORKFLOW_WORKFLOW_H
