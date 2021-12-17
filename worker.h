#ifndef WORKFLOW_WORKER_H
#define WORKFLOW_WORKER_H

#include <string>
#include <vector>
#include "exceptions.h"

struct Worker {
    virtual void run(std::vector<std::string> &buffer) const = 0;
    virtual std::string name() = 0;
    virtual ~Worker() = default;
};

#endif //WORKFLOW_WORKER_H
