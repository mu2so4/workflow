#ifndef WORKFLOW_ABSTRACT_FACTORY_H
#define WORKFLOW_ABSTRACT_FACTORY_H

#include "worker.h"

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual Worker *createWorker() = 0;
};


#endif //WORKFLOW_ABSTRACT_FACTORY_H
