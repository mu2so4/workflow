#ifndef WORKFLOW_WORKER_H
#define WORKFLOW_WORKER_H

#include <string>
#include "buffer.h"
#include "exceptions.h"

class Worker {
public:
    virtual void run(const std::string &params, Buffer &buffer) const = 0;
    virtual ~Worker() = default;
};

#endif //WORKFLOW_WORKER_H
