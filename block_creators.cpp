#include "block_creators.h"

Worker *ReaderCreator::createWorker(const std::string &params) {
    if(params.empty()) {
        throw ArgumentException("too few arguments for readfile\n");
    }
    return new FileReader(params);
}

Worker *DumperCreator::createWorker(const std::string &params) {
    if(params.empty()) {
        throw ArgumentException("too few arguments for dump\n");
    }
    return new FileDumper(params);
}

Worker *WriterCreator::createWorker(const std::string &params) {
    if(params.empty()) {
        throw ArgumentException("too few arguments for writefile\n");
    }
    return new FileWriter(params);
}

Worker *SorterCreator::createWorker(const std::string &params) {
    if(!params.empty()) {
        throw ArgumentException("sort shouldn't have any params\n");
    }
    return new Sorter();
}

Worker *GrepCreator::createWorker(const std::string &params) {
    if(params.empty()) {
        throw ArgumentException("too few arguments for grep\n");
    }
    return new Grepper(params);
}

Worker *ReplacerCreator::createWorker(const std::string &params) {
    auto delim = params.find(' ');
    if(delim == std::string::npos) {
        throw ArgumentException("too few arguments for replacement\n");
    }
    return new Replacer(params.substr(0, delim), params.substr(delim + 1));
}
