#ifndef WORKFLOW_FACTORY_H
#define WORKFLOW_FACTORY_H

#include <map>
#include "creator.h"
#include "worker.h"
#include "block_creators.h"

class WorkerFactory {
    std::map<std::string, WorkerCreator*> creators;

    WorkerFactory();
public:
    ~WorkerFactory();

    void registerMaker(const std::string &key, WorkerCreator *creator);
    Worker *createWorker(const std::string &params) const;

    static WorkerFactory &instance();
};


#endif //WORKFLOW_FACTORY_H
