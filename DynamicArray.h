#pragma once
#include <vector>
#include "Dog.h"
#include <string>

template<class T>
class DynamicArray {
private:
    std::vector<T> data;

public:
    DynamicArray() : data(10) {}
    DynamicArray(int capacity) : data(capacity) {}
    DynamicArray(const DynamicArray&) = default;
    ~DynamicArray() = default;

    T& operator[](int i) const {
        if (i < 0 || i >= data.size())
            throw INDEX_ERROR;
        return data[i];
    }

    DynamicArray& operator=(const DynamicArray& v) {
        if (this == &v)
            return *this;
        data = v.data;
        return *this;
    }

    void push_back(T elem) {
        data.push_back(elem);
    }

    void erase(int index) {
        if (index < 0 || index >= data.size())
            throw INDEX_ERROR;
        data.erase(data.begin() + index);
    }

    bool isEmpty() const {
        return data.empty();
    }

    bool isFull() const {
        return false;
    }

    int size() const {
        return data.size();
    }
};

template class DynamicArray<Dog>;
template class DynamicArray<std::string>;
template class DynamicArray<int>;