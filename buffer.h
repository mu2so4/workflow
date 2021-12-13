#ifndef WORKFLOW_BUFFER_H
#define WORKFLOW_BUFFER_H

#include <string>

struct Buffer {
    std::string *data = nullptr;
    int size = 0;
    bool isLoaded = false;
    bool isSaved = false;
    bool isDumped = false;

    Buffer() = default;

    void loadData(std::string *arr, int count) {
        delete[] data;
        data = arr;
        size = count;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
    }

    ~Buffer() {
        delete[] data;
    }
};

#endif //WORKFLOW_BUFFER_H
