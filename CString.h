#ifndef CSTRING_INCLUDED
#define CSTRING_INCLUDED

#include <cwchar>
#include <vector>
#include "Sequence.h"

template <class T>
class CString {
    Sequence<T> *data;

public:
    explicit CString(Sequence<T> *sequence) : data(sequence) {};
    //Деструктор
    ~CString() {
        delete data;
        data = nullptr;
    }

    bool empty() const {
        return data->getLength() == 0;
    }
    int getLength() const {
        return data->getLength();
    }
    void push(T item) {
        data->append(item);
    }

    T deletesymbol(int i) {
        data->removeAt(i);
    }
    T operator[](int i) const {
        return data->get(i);
    }
    T &operator[](int i) {
        return data->get(i);
    }
    CString<T> *concat(CString<T> &string) {
        return new CString<T>(data->concat(string.data));
    }

    bool equals(CString<T> &string1, CString<T> &string2) {
        if (string1.data->getLength() != string2.data->getLength()) {
            return false;
        }else{
            for (int i = 0; i < string1.data->getLength(); i++) {
                if (string1.data->get(i) != string2.data->get(i)) {
                    return false;
                }
            }
            return true;
        }
    }

    Sequence<T> *getSubsequence(int startIndex, int endIndex) const {
        return data->getSubsequence(startIndex, endIndex);
    }
    // Поиск подпоследовательности
    int findSubsequence(CString<T> &string) {
        return data->findSubsequence(*string.data);
    }


    explicit CString(Sequence<T> *sequence, const wchar_t *string) : data(sequence) {
            std::wcout << string << std::endl;
            int N;
            wprintf(L"Введите количество элементов: ");
            std::wcin >> N;
            // Вводим элементы по одному
            for (int i = 0; i < N; i++) {
                wprintf(L"Введите элемент с индексом %d: ", i);
                T element;
                std::wcin >> element;
                push(element);  // Добавляем его на вершину стека
                // print(); // Текущее состояние стека
            }
    }
    void print() {
        std::wcout << L"String size = " << data->getLength() << std::endl;
        for (int i = 0; i < data->getLength(); i++) {
            std::wcout << data->get(i) << L" ";
        }
        wcout << std::endl;
    }
};

#endif

