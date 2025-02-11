#ifndef DYNAMICARRAY_INCLUDED
#define DYNAMICARRAY_INCLUDED

#include <cstring>
#include <iostream>

#include "Common.h"

template<class T>
class DynamicArray {
    int size;
    T *data;
    bool *defined;  // Задан ли элемент массива?

    void checkIndex(int index) const {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange(string("Index ") + to_string(index) + " out of range 0.." + to_string(size - 1));
        }
    }

public:
    //Создание объекта

    DynamicArray(T *items, int count) : size(count) {
        if (size < 0) throw IndexOutOfRange("Size < 0");
        data = new T[size];
        defined = new bool[size];
        memcpy(data, items, sizeof(T) * size);
        for (int i = 0; i < size; i++) {
            defined[i] = true;
        }
    };

    explicit DynamicArray(int count = 0) : size(count) {
        if (size < 0) throw IndexOutOfRange("Count < 0");
        data = new T[size];
        defined = new bool[size];
        for (int i = 0; i < size; i++) {
            defined[i] = false;
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray) {
        size = dynamicArray.size;
        // Копируем элементы
        data = new T[dynamicArray.size];
        memcpy(data, dynamicArray.data, dynamicArray.size * sizeof(T));
        // Копируем какие элементы определены
        defined = new bool[dynamicArray.size];
        memcpy(defined, dynamicArray.defined, dynamicArray.size * sizeof(bool));
    }

    //Деструктор
    ~DynamicArray() {
        delete[] data;
        data = nullptr;
        delete[] defined;
        defined = nullptr;
    }

    //Декомпозиция
    T &get(int index) const {
        checkIndex(index);
        if (!defined[index]) {
            throw IndexOutOfRange(string("Element with index ") + to_string(index) + " not defined");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    //Операции
    void set(int index, T value) {
        checkIndex(index);
        data[index] = value;
        defined[index] = true;
    }

    T operator[](size_t index) const {  // Получение значения
        return get(index);
    }

    T &operator[](size_t index) {  // Чтобы делать присваивание так: dynamicArray[1] = 1233;
        checkIndex(index);
        defined[index] = true;
        return data[index];
    }

    void resize(int newSize) {
        if (newSize < 0) {
            throw bad_array_new_length();
        }
        T *newData = new T[newSize];
        bool *newDefined = new bool[newSize];
        for (int i = 0; i < min(size, newSize); i++) {
            newData[i] = data[i];
            newDefined[i] = defined[i];
        }
        memcpy(newData, data, sizeof(T) * min(size, newSize));
        memcpy(newDefined, defined, sizeof(bool) * min(size, newSize));
        for (int i = size; i < newSize; i++) {
            newDefined[i] = false;
        }
        size = newSize;
        delete[] data;
        data = newData;
        delete[] defined;
        defined = newDefined;
    }
    void define_resize(int newSize) {
        for (int i = newSize - 1; i >= 1; i--) {
            defined[i] = defined[i - 1];
        }
    }

    void define_set(int index, bool value) {
        defined[index] = value;
    }
};

#endif
