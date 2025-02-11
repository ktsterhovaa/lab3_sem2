//
// Created by dimak on 04.05.2024.
//

#ifndef LAB3_DEQUE_H
#define LAB3_DEQUE_H
#include <cwchar>
#include <iostream>
#include "Sequence.h"
#include "FunctionHolder.h"
#include "Functions.h"
using namespace std;

template <class T>
class Deque {
    Sequence<T> *data;

public:
    explicit Deque(Sequence<T> *sequence) : data(sequence) {};

    // Деструктор
    ~Deque() {
        delete data;
        data = nullptr;
    }

    // Проверка на пустоту
    bool empty() const {
        return data->getLength() == 0;
    }

    // Получение размера дека
    int getLength() const {
        return data->getLength();
    }

    // Добавление элемента в начало дека
    void pushFront(T item) {
        data->prepend(item);
    }

    // Добавление элемента в конец дека
    void pushBack(T item) {
        data->append(item);
    }

    // Удаление и возврат элемента из начала дека
    T popFront() {
        T value = data->getFirst();
        data->removeAt(0);
        return value;
    }

    // Удаление и возврат элемента из конца дека
    T popBack() {
        T value = data->getLast();
        data->removeAt(data->getLength() - 1);
        return value;
    }

    // Получение элемента по индексу
    T operator[](int i) const {
        return data->get(i);
    }

    // Применение функции к каждому элементу дека
    Deque<T> *map(T (*f)(T)) {
        return new Deque<T>(data->map(f));
    }

    // Фильтрация элементов дека по условию
    Deque<T> *where(bool (*h)(T)) {
        return new Deque<T>(data->where(h));
    }

    // Сворачивание элементов дека с помощью функции
    T reduce(T (*f)(T, T)) {
        return data->reduce(f);
    }

    // Объединение двух деков
    Deque<T> *concat(Deque<T> &deque) {
        return new Deque<T>(data->concat(deque.data));
    }

    void print(Deque<int> *deque) {
        wcout << L"Deque size = " <<deque-> data->getLength() << endl;
        for (int i = 0; i <deque-> data->getLength(); i++) {
            wcout <<deque-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Deque<double> *deque) {
        wcout << L"Deque size = " <<deque-> data->getLength() << endl;
        for (int i = 0; i <deque-> data->getLength(); i++) {
            wcout <<deque-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Deque<wstring> *deque) {
        wcout << L"Deque size = " <<deque-> data->getLength() << endl;
        for (int i = 0; i <deque-> data->getLength(); i++) {
            wcout <<deque-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Deque<std::complex<double>> *deque) {
        wcout << L"Deque size = " <<deque-> data->getLength() << endl;
        for (int i = 0; i <deque-> data->getLength(); i++) {
            wcout <<deque-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Deque<Person> *deque) {
        wcout << L"Deque size = " <<deque-> data->getLength() << endl;
        for (int i = 0; i <deque-> data->getLength(); i++) {
            wcout <<L"ID: "<<deque-> data->get(i).GetID().id<< L" Фамилия: "<< deque-> data->get(i).GetLastName() << L" Имя: "<< deque-> data->get(i).GetFirstName() << L" Отчество: "<< deque-> data->get(i).GetMiddleName() << L"| ";
        }
        wcout << endl;
    }
    void print(Deque<FunctionHolder> *deque) {
        wcout << L"Deque size = " <<deque-> data->getLength() << endl;
        wprintf(L"Введите два целых числа: ");
        int a, b;
        wcin >> a >> b;
        for (int i = 0; i <deque-> data->getLength(); i++) {
            wcout << L"Результат функции " << deque->data->get(i).name
                  << L": " << to_wstring((deque->data->get(i).funcPtr)(a, b)) << L"| ";
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

    // Конструктор для ввода элементов дека
    explicit Deque(Sequence<T> *sequence, const wchar_t *string) : data(sequence) {
        wcout << string << endl;
        int N;
        wprintf(L"Введите количество элементов: ");
        wcin >> N;
        // Вводим элементы по одному
        for (int i = 0; i < N; i++) {
            wprintf(L"Введите элемент с индексом %d: ", i);
            T element;
            filldata(&element);
            // Выбор, куда добавить элемент:
            wprintf(L"Добавить в начало (0) или конец (1)? ");
            int choice;
            wcin >> choice;
            if (choice == 0) {
                pushFront(element);
            } else {
                pushBack(element);
            }
            // print(); // Текущее состояние дека
        }
    }

    // Получение подпоследовательности
    Sequence<T> *getSubsequence(int startIndex, int endIndex) const {
        return data->getSubsequence(startIndex, endIndex);
    }

    // Поиск подпоследовательности
    int findSubsequence(Deque<T> &deque) {
        return data->findSubsequence(*deque.data);
    }
};

#endif //LAB3_DEQUE_H
