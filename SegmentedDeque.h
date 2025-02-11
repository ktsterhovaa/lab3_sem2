#ifndef LAB3_SEGMENTEDDEQUE_H
#define LAB3_SEGMENTEDDEQUE_H

#include <cwchar>
#include <iostream>
#include <vector>
#include "Sequence.h"
#include "FunctionHolder.h"
#include "Functions.h"
#include "Person.h"

using namespace std;

template <class T>
class SegmentedDeque {
private:
    vector<Sequence<T>*> segments;
    int segmentSize;
    int frontSegment;
    int backSegment;
    int frontIndex;
    int backIndex;

    // Функция для добавления нового сегмента в начало
    void addFrontSegment() {
        segments.insert(segments.begin(), new ArraySequence<T>());
        frontSegment = 0;
        frontIndex = segmentSize - 1;
        backSegment++;
    }

    // Функция для добавления нового сегмента в конец
    void addBackSegment() {
        segments.push_back(new ArraySequence<T>());
        backSegment = segments.size() - 1;
        backIndex = 0;
    }

public:
    // Конструктор
    explicit SegmentedDeque(int segmentSize = 10) : segmentSize(segmentSize), frontSegment(0), backSegment(0), frontIndex(0), backIndex(0) {
        addFrontSegment();
        addBackSegment();
    }

    // Деструктор
    ~SegmentedDeque() {
        for (auto segment : segments) {
            delete segment;
        }
    }

    // Проверка на пустоту
    bool empty() const {
        return segments.size() == 1 && segments[0]->getLength() == 0;
    }

    // Получение размера дека
    int getLength() const {
        int size = 0;
        for (const auto& segment : segments) {
            size += segment->getLength();
        }
        return size;
    }

    // Добавление элемента в начало дека
    void pushFront(const T item) {
        if (frontIndex ==-1) {
            addFrontSegment();
        }
        segments[frontSegment]->prepend(item);
        frontIndex--;
    }

    // Добавление элемента в конец дека
    void pushBack(const T item) {
        if (backIndex==segmentSize) {
            addBackSegment();
        }
        segments[backSegment]->append(item);
        backIndex++;
    }

    // Удаление и возврат элемента из начала дека
    T popFront() {
        if (empty()) {
            throw runtime_error("Deque is empty");
        }
        T value = segments[frontSegment]->get(0);
        if (frontIndex==(segmentSize-1)) {
            segments.erase(segments.begin());
            backSegment--;
            frontIndex=segmentSize-segments[frontSegment]->getLength()-1;
            if (segments.size() == 0) {
                throw runtime_error("Deque is empty");
            }
            //popFront();
        }
        if (frontIndex!=(segmentSize-1)){
            segments[frontSegment]->removeAt(0);
            frontIndex++;
        }
        return value;
    }

    // Удаление и возврат элемента из конца дека
    T popBack() {
        if (empty()) {
            throw runtime_error("Deque is empty");
        }
        T value = segments[backSegment]->operator[](segments[backSegment]->getLength() - 1);
        if (backIndex==0) {
            segments.pop_back();
            backSegment--;
            backIndex=segments[backSegment]->getLength();
            if (segments.size() == 0) {
                throw runtime_error("Deque is empty");
            }
            popFront();
        }else {
            segments[backSegment]->removeAt(segments[backSegment]->getLength() - 1);
            backIndex--;
        }
        return value;
    }

    // Получение элемента по индексу
    T operator[](int i) const {
        if (i < 0 || i >= getLength()) {
            throw out_of_range("Index out of range");
        }
        int indexInSegment;
        int k=0;
        int segmentIndex = (i+(segmentSize-segments[frontSegment]->getLength()))/segmentSize;
        if (segmentIndex==0){
            indexInSegment = i;
            k=segmentSize-segments[frontSegment]->getLength();
        }else{
            indexInSegment = (i+k)%segmentSize;
        }
        return segments[segmentIndex]->get(indexInSegment);
    }

    void print(SegmentedDeque<int> *segmentedDeque) {
        wcout << L"Segmented Deque size = " <<segmentedDeque->getLength() << endl;
        for (auto segment : segmentedDeque->segments) {
            for (int i = 0; i <segment->getLength(); i++) {
                wcout <<segment->get(i) << L" ";
            }
        }
        wcout << endl;
    }
    void print(SegmentedDeque<double> *segmentedDeque) {
        wcout << L"SegmentedDeque size = " <<segmentedDeque->getLength() << endl;
        for (auto segment : segmentedDeque->segments) {
            for (int i = 0; i <segment->getLength(); i++) {
                wcout <<segment->get(i) << L" ";
            }
        }
        wcout << endl;
    }
    void print(SegmentedDeque<wstring> *segmentedDeque) {
        wcout << L"SegmentedDeque size = " <<segmentedDeque->getLength() << endl;
        for (auto segment : segmentedDeque->segments) {
            for (int i = 0; i <segment->getLength(); i++) {
                wcout <<segment->get(i) << L" ";
            }
        }
        wcout << endl;
    }
    void print(SegmentedDeque<std::complex<double>> *segmentedDeque) {
        wcout << L"SegmentedDeque size = " <<segmentedDeque->getLength() << endl;
        for (auto segment : segmentedDeque->segments) {
            for (int i = 0; i <segment->getLength(); i++) {
                wcout <<segment->get(i) << L" ";
            }
        }
        wcout << endl;
    }
    void print(SegmentedDeque<Person> *segmentedDeque) {
        wcout << L"SegmentedDeque size = " <<segmentedDeque->getLength() << endl;
        for (auto segment : segmentedDeque->segments) {
            for (int i = 0; i <segment->getLength(); i++) {
                wcout <<L"ID: "<<segment->get(i).GetID().id<< L" Фамилия: "<<segment->get(i).GetLastName() << L" Имя: "<<segment->get(i).GetFirstName() << L" Отчество: "<<segment->get(i).GetMiddleName() << L"| ";
            }
        }
        wcout << endl;
    }
    void print(SegmentedDeque<FunctionHolder> *segmentedDeque) {
        wcout << L"SegmentedDeque size = " <<segmentedDeque->getLength() << endl;
        wprintf(L"Ввеите два целых числа: ");
        int a, b;
        wcin >> a >> b;
        for (auto segment : segmentedDeque->segments) {
            for (int i = 0; i <segment->getLength(); i++) {
                wcout << L"Результат функции " << segment->get(i).name
                      << L": " << to_wstring((segment->get(i).funcPtr)(a, b)) << L"| ";            }
        }
        wcout << endl;
    }

    void filldata(int *item) {
        wprintf(L"Введите элемент: ");
        wcin >> *item;

    }
    void filldata(double *item) {
        wprintf(L"Введите элемент: ");
        wcin >> *item;

    }
    void filldata(wstring *item) {
        wprintf(L"Введите элемент: ");
        wcin >> *item;
    }
    void filldata(std::complex<double> *item) {
        wprintf(L"Введите элемент: ");
        wcin >> *item;
    }
    void filldata(Person *person) {
        wprintf(L"Введите Id: ");
        int id;
        wcin >> id;
        person->SetID(id);
        wprintf(L"Введите имя: ");
        wstring firstName;
        wcin >> firstName;
        wprintf(L"Введите отчество: ");
        wstring middleName;
        wcin >> middleName;
        wprintf(L"Введите фамилию: ");
        wstring lastName;
        wcin >> lastName;
        person->SetFirstName(firstName);
        person->SetMiddleName(middleName);
        person->SetLastName(lastName);
    }
    void filldata(FunctionHolder *holder) {
        Functions functions;
        wprintf(L"Ввод номера функции, которую хотите добавить: \n");
        wprintf(L"1-функция сложения\n");
        wprintf(L"2-функция вычитания\n");
        wprintf(L"3-функция умножения  \n");
        wprintf(L"Введите номер: ");
        int condition;
        wcin >> condition;
        switch (condition) {
            case 1:{
                holder->funcPtr = &functions.Add;
                holder->name=L"Сложение";
                break;
            }
            case 2:{
                holder->funcPtr = &functions.Sub;
                holder->name=L"Вычитание";
                break;
            }
            case 3:{
                holder->funcPtr = &functions.Mult;
                holder->name=L"Умножение";
                break;
            }
            default:
                break;
        }
    }

    explicit SegmentedDeque(int segmentSize = 10, const wchar_t *string=L"SegmentedDeque") : segmentSize(segmentSize), frontSegment(0), backSegment(0), frontIndex(0), backIndex(0) {
        wcout << string << endl;
        addFrontSegment();
        addBackSegment();
        int N;
        wprintf(L"Введите количество элементов: ");
        wcin >> N;
        for (int i = 0; i < N; i++) {
            wprintf(L"Ввод элемента с индексом %d ", i);
            T element;
            filldata(&element);// Заполняем элемент()
            int method_of_push;
            wprintf(L"Добавить в начало (1) или конец (0)? ");
            wcin >> method_of_push;
            if (method_of_push==1){
            pushFront(element);
            }
            else if(method_of_push==0){
            pushBack(element);
            }else{
                throw IndexOutOfRange("method_of_push=" + to_string(method_of_push) + " != 0 || 1");
            }
        }

    }
};

#endif
