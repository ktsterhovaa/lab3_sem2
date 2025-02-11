#ifndef LAB3_QUEUE_H
#define LAB3_QUEUE_H

#include <cwchar>
#include <iostream>
#include "Sequence.h"
#include "FunctionHolder.h"
#include "Functions.h"
using namespace std;

template <class T>
class Queue {
    Sequence<T> *data;

public:
    explicit Queue(Sequence<T> *sequence) : data(sequence) {};
    //Деструктор
    ~Queue() {
        delete data;
        data = nullptr;
    }
    // Пустая ли очередь?
    bool empty() const {
        return data->getLength() == 0;
    }
    int getLength() const {
        return data->getLength();
    }
    // Добавление элемента в конец очереди
    void enqueue(T item) {
        data->append(item);
    }
    // Извлечение элемента из начала очереди
    T dequeue() {
        T value = data->getFirst();
        data->removeAt(0);
        return value;
    }
    T operator[](int i) const {
        return data->get(i);
    }
    Queue<T> *map(T (*f)(T)) {
        return new Queue<T>(data->map(f));
    }
    Queue<T> *where(bool (*h)(T)) {
        return new Queue<T>(data->where(h));
    }
    T reduce(T (*f)(T, T)) {
        return data->reduce(f);
    }
    Queue<T> *concat(Queue<T> &queue) {
        return new Queue<T>(data->concat(queue.data));
    }

    void print(Queue<int> *queue) {
        wcout << L"Queue size = " <<queue-> data->getLength() << endl;
        for (int i = 0; i <queue-> data->getLength(); i++) {
            wcout <<queue-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Queue<double> *queue) {
        wcout << L"Queue size = " <<queue-> data->getLength() << endl;
        for (int i = 0; i <queue-> data->getLength(); i++) {
            wcout <<queue-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Queue<wstring> *queue) {
        wcout << L"Queue size = " <<queue-> data->getLength() << endl;
        for (int i = 0; i <queue-> data->getLength(); i++) {
            wcout <<queue-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Queue<std::complex<double>> *queue) {
        wcout << L"Queue size = " <<queue-> data->getLength() << endl;
        for (int i = 0; i <queue-> data->getLength(); i++) {
            wcout <<queue-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Queue<Person> *queue) {
        wcout << L"Stack size = " <<queue-> data->getLength() << endl;
        for (int i = 0; i <queue-> data->getLength(); i++) {
            wcout <<L"ID: "<<queue-> data->get(i).GetID().id<< L" Фамилия: "<< queue-> data->get(i).GetLastName() << L" Имя: "<< queue-> data->get(i).GetFirstName() << L" Отчество: "<< queue-> data->get(i).GetMiddleName() << L"| ";
        }
        wcout << endl;
    }
    void print(Queue<FunctionHolder> *queue) {
        wcout << L"Queue size = " <<queue-> data->getLength() << endl;
        wprintf(L"Введите два целых числа: ");
        int a, b;
        wcin >> a >> b;
        for (int i = 0; i <queue-> data->getLength(); i++) {
            wcout << L"Результат функции " << queue->data->get(i).name
                  << L": " << to_wstring((queue->data->get(i).funcPtr)(a, b)) << L"| ";
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
    // Конструктор для ввода элементов очереди
    explicit Queue(Sequence<T> *sequence, const wchar_t *string) : data(sequence) {
        wcout << string << endl;
        int N;
        wprintf(L"Введите количество элементов: ");
        wcin >> N;
        // Вводим элементы по одному
        for (int i = 0; i < N; i++) {
            wprintf(L"Введите элемент с индексом %d: ", i);
            T element;
            filldata(&element);
            enqueue(element);  // Добавляем его в конец очереди
            // print(); // Текущее состояние очереди
        }
    }
    Sequence<T> *getSubsequence(int startIndex, int endIndex) const {
        return data->getSubsequence(startIndex, endIndex);
    }
    // Поиск подпоследовательности
    int findSubsequence(Queue<T> &queue) {
        return data->findSubsequence(*queue.data);
    }
};

#endif

