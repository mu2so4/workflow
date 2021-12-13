#include "block_creators.h"

Worker *ReaderCreator::createWorker() {
    return new FileReader();
}

Worker *DumperCreator::createWorker() {
    return new FileDumper();
}

Worker *WriterCreator::createWorker() {
    return new FileWriter();
}

Worker *SorterCreator::createWorker() {
    return new Sorter();
}

Worker *GrepCreator::createWorker() {
    return new Grepper();
}

Worker *ReplacerCreator::createWorker() {
    return new Replacer();
}
