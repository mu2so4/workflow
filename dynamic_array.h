#ifndef WORKFLOW_DYNAMIC_ARRAY_H
#define WORKFLOW_DYNAMIC_ARRAY_H

#include <algorithm>

template<class T>
class DynamicArray {
    T *array;
    int elementCount;
    int containerSize;

public:
    DynamicArray();
    ~DynamicArray();

    void pushBack(const T &a);

    std::pair<T*, int> exportData();

private:
    void resize();
};




template<class T>
DynamicArray<T>::DynamicArray():
        elementCount(0),
        containerSize(6)
{
    array = new T[containerSize];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] array;
    array = nullptr;
}

template<class T>
void DynamicArray<T>::pushBack(const T &a) {
    if(elementCount == containerSize)
        resize();
    array[elementCount] = a;
    elementCount++;
}

template<class T>
std::pair<T*, int> DynamicArray<T>::exportData() {
    T *alignedArr = new T[elementCount];
    int size = elementCount;

    for(int index = 0; index < elementCount; index++) {
        alignedArr[index] = std::move(array[index]);
    }
    delete[] array;
    array = nullptr;
    elementCount = containerSize = 0;
    return std::pair<T*, int>{alignedArr, size};
}

template<class T>
void DynamicArray<T>::resize() {
    int newSize = containerSize * 3 / 2 + 1;
    T *newArr = new T[newSize];
    for(int index = 0; index < containerSize; index++) {
        newArr[index] = std::move(array[index]);
    }
    delete[] array;
    array = newArr;
    containerSize = newSize;
}


#endif //WORKFLOW_DYNAMIC_ARRAY_H
