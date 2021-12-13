#ifndef WORKFLOW_BLOCK_CREATORS_H
#define WORKFLOW_BLOCK_CREATORS_H

#include "abstract_factory.h"
#include "blocks.h"

class ReaderCreator: public AbstractFactory {
    Worker *createWorker() override;
};

class DumperCreator: public AbstractFactory {
    Worker *createWorker() override;
};

class WriterCreator: public AbstractFactory {
    Worker *createWorker() override;
};

class SorterCreator: public AbstractFactory {
    Worker *createWorker() override;
};

class GrepCreator: public AbstractFactory {
    Worker *createWorker() override;
};

class ReplacerCreator: public AbstractFactory {
    Worker *createWorker() override;
};

#endif //WORKFLOW_BLOCK_CREATORS_H
