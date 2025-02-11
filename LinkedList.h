#ifndef LINKEDLIST_INCLUDED
#define LINKEDLIST_INCLUDED

#include <iostream>

#include "Common.h"
#include "Person.h"


template<class T>
class LinkedList {
    struct Node {
        T value;
        Node *prev;
        Node *next;

        Node(T value, Node *prev = nullptr, Node *next = nullptr) : value(value), prev(prev), next(next) {}
    };

    Node *first = nullptr;
    Node *last = nullptr;
    int size = 0;

public:
    //Конструкторы
    LinkedList(T *items, int count) {  // Копировать элементы из переданного массива
        for (int i = 0; i < count; i++) {
            append(items[i]);
        }
    }

    LinkedList() {};

    // Копирующий конструктор
    LinkedList(const LinkedList<T> &list) : size(list.size) {
        for (Node *n = list.first; n != nullptr; n = n->next) {
            auto *node = new Node(n->value, last, nullptr);
            if (first == nullptr) first = node;
            if (last != nullptr) last->next = node;
            last = node;
        }
    }

    //Деструктор
    ~LinkedList() {
        while (first != nullptr) {
            Node *toDelete = first;
            first = first->next;
            delete toDelete;
        }
        last = nullptr;
    }

    //Декомпозиция
    T getFirst() const {
        if (first == nullptr) throw IndexOutOfRange("List is empty");
        return first->value;
    }

    T getLast() const {
        if (last == nullptr) throw IndexOutOfRange("List is empty");
        return last->value;
    }

    T &get(int index) const {
        if (index < 0)
            throw IndexOutOfRange(
                    string("Index ") + to_string(index) + " out of range 0.." + to_string(getLength() - 1));
        int idx = 0;
        for (Node *n = first; n != nullptr; n = n->next) {
            if (idx == index) return n->value;
            idx++;
        }
        throw IndexOutOfRange(string("Index ") + to_string(index) + " out of range 0.." + to_string(getLength() - 1));
    }

    // Перегруженные операторы
    T operator[](int i) const {
        return get(i);
    }

    T &operator[](int i) {
        return get(i);
    }

    LinkedList<T> *getSubList(int startIndex, int endIndex) {
        if (startIndex < 0)
            throw IndexOutOfRange(string("startIndex ") + to_string(startIndex) + " out of range 0.." +
                                  to_string(getLength() - 1));
        if (endIndex < 0)
            throw IndexOutOfRange(string("endIndex ") + to_string(endIndex) + " out of range 0.." +
                                  to_string(getLength() - 1));
        if (startIndex > endIndex)
            throw IndexOutOfRange(string("startIndex=") + to_string(startIndex) + " > endIndex=" + to_string(endIndex));
        Node *cur = first;
        for (int i = 0; i < startIndex && cur != nullptr; i++) cur = cur->next;
        auto *subList = new LinkedList<T>();
        for (int i = startIndex; i <= endIndex; i++) {
            subList->append(cur->value);
            cur = cur->next;
        }
        return subList;
    }

    int getLength() const {
        return size;
    }

    //Операции
    void append(T item) {
        auto *n = new Node(item, last, nullptr);
        if (first == nullptr) {
            first = n;
        }
        if (last != nullptr) {
            last->next = n;
        }
        last = n;
        size++;
    }

    void prepend(T item) {
        auto *node = new Node(item, nullptr, first);
        if (first != nullptr) {
            first->prev = node;
        }
        first = node;
        if (last == nullptr) {
            last = node;
        }
        size++;
    }

    void insertAt(T item, int index) {
        if (index < 0) {
            throw IndexOutOfRange(string("insertAt index=") + to_string(index) + " < 0");
        }
        if (index > getLength()) {
            throw IndexOutOfRange(string("insertAt index=") + to_string(index) + " >= getLength()");
        }
        if (index == 0) {
            prepend(item);
            return;
        }
        Node *cur = first;
        for (int i = 0; i < index - 1 && cur != nullptr; i++) {
            cur = cur->next;
        }
        auto *n = new Node(item, cur, cur->next);
        cur->next = n;
        if (n->next == nullptr) {
            last = n;
        } else {
            n->next->prev = n;
        }
        size++;
    }

    LinkedList<T> *concat(LinkedList<T> *list) {
        auto *res = new LinkedList<T>(*this);
        for (Node *n = list->first; n != nullptr; n = n->next) {
            res->append(n->value);
        }
        return res;
    }

    void removeAt(int index) {
        if (index < 0) {
            throw IndexOutOfRange(string("removeAt index=") + to_string(index) + " < 0");
        }
        if (index > getLength()) {
            throw IndexOutOfRange(string("removeAt index=") + to_string(index) + " >= getLength()");
        }
        Node *toDelete = first;
        for (int i = 0; i < index; i++) {
            toDelete = toDelete->next;
        }
        if (toDelete == first) {
            first = toDelete->next;
        }
        // Если это последний
        if (toDelete == last) {
            last = toDelete->prev;
        }
        if (toDelete->prev != nullptr) {
            toDelete->prev->next = toDelete->next;
        }
        if (toDelete->next != nullptr) {
            toDelete->next->prev = toDelete->prev;
        }
        delete toDelete;
        size--;
    }

    //Итератор
    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator(Node *ptr) : m_ptr(ptr) {}

        reference operator*() const {
            return m_ptr->value;
        }
        pointer operator->() {
            return m_ptr->value;
        }
        Iterator &operator++() {
            m_ptr = m_ptr->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.m_ptr == b.m_ptr;
        };
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.m_ptr != b.m_ptr;
        };

    private:
        Node *m_ptr;
    };

    Iterator begin() {
        return Iterator(first);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
};

#endif

