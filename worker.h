#ifndef WORKFLOW_WORKER_H
#define WORKFLOW_WORKER_H

#include <string>

class Worker {
public:
    virtual void run(const std::string &params) const = 0;
    virtual ~Worker() = default;
};

#endif //WORKFLOW_WORKER_H
