#ifndef WORKFLOW_BLOCK_CREATORS_H
#define WORKFLOW_BLOCK_CREATORS_H

#include "factory.h"
#include "creator.h"
#include "blocks.h"

class ReaderCreator: public WorkerCreator {
    Worker *createWorker(const std::string &params) override;
};

class DumperCreator: public WorkerCreator {
    Worker *createWorker(const std::string &params) override;
};

class WriterCreator: public WorkerCreator {
    Worker *createWorker(const std::string &params) override;
};

class SorterCreator: public WorkerCreator {
    Worker *createWorker(const std::string &params) override;
};

class GrepCreator: public WorkerCreator {
    Worker *createWorker(const std::string &params) override;
};

class ReplacerCreator: public WorkerCreator {
    Worker *createWorker(const std::string &params) override;
};

#endif //WORKFLOW_BLOCK_CREATORS_H
