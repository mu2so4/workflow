#include "factory.h"

WorkerFactory::WorkerFactory() {
    registerMaker("readfile", new ReaderCreator());
    registerMaker("writefile", new WriterCreator());
    registerMaker("dump", new DumperCreator());
    registerMaker("sort", new SorterCreator());
    registerMaker("replace", new ReplacerCreator());
    registerMaker("grep", new GrepCreator());
}

void WorkerFactory::registerMaker(const std::string &key, WorkerCreator *creator) {
    if(creators.find(key) != creators.end())
        throw ConfigFileFormatException("operator with the key \"" + key + "\" already exists\n");
    creators.insert(std::pair<std::string, WorkerCreator*>(key, creator));
}

Worker *WorkerFactory::createWorker(const std::string &params) const {
    auto pos = params.find(' ');
    std::string cmd = params.substr(0, pos);
    auto iter = creators.find(cmd);
    if(iter == creators.end())
        throw ConfigFileFormatException("operator \"" + cmd + "\" is undefined\n");
    if(pos == std::string::npos)
        return iter->second->createWorker("");
    return iter->second->createWorker(params.substr(pos + 1));
}

WorkerFactory &WorkerFactory::instance() {
    static WorkerFactory factory;

    return factory;
}

WorkerFactory::~WorkerFactory() {
    for(auto &iter: creators)
        delete iter.second;
}

