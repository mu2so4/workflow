#ifndef WORKFLOW_CREATOR_H
#define WORKFLOW_CREATOR_H

#include "worker.h"

class WorkerCreator {
public:
    virtual Worker *createWorker(const std::string &params) = 0;
    virtual ~WorkerCreator() = default;
};

#endif //WORKFLOW_CREATOR_H
