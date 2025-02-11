#ifndef STACK_INCLUDED
#define STACK_INCLUDED
#include "Sequence.h"
#include "Person.h"
#include "FunctionHolder.h"
#include "Functions.h"

template <class T>
class Stack {
    Sequence<T> *data;
public:
    explicit Stack(Sequence<T> *sequence) : data(sequence) {};
    ~Stack() {
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
    T pop() {
        T value = data->getLast();
        data->removeAt(data->getLength() - 1);
        return value;
    }
    T operator[](int i) const {
        return data->get(i);
    }
    Stack<T> *map(T (*f)(T)) {
        return new Stack<T>(data->map(f));
    }
    Stack<T> *where(bool (*h)(T)) {
        return new Stack<T>(data->where(h));
    }
    T reduce(T (*f)(T, T)) {
        return data->reduce(f);
    }
    Stack<T> *concat(Stack<T> &stack) {
        return new Stack<T>(data->concat(stack.data));
    }
    void print(Stack<int> *stack) {
        wcout << L"Stack size = " <<stack-> data->getLength() << endl;
        for (int i = 0; i <stack-> data->getLength(); i++) {
            wcout <<stack-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Stack<double> *stack) {
        wcout << L"Stack size = " <<stack-> data->getLength() << endl;
        for (int i = 0; i <stack-> data->getLength(); i++) {
            wcout <<stack-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Stack<wstring> *stack) {
        wcout << L"Stack size = " <<stack-> data->getLength() << endl;
        for (int i = 0; i <stack-> data->getLength(); i++) {
            wcout <<stack-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Stack<std::complex<double>> *stack) {
        wcout << L"Stack size = " <<stack-> data->getLength() << endl;
        for (int i = 0; i <stack-> data->getLength(); i++) {
            wcout <<stack-> data->get(i) << L" ";
        }
        wcout << endl;
    }
    void print(Stack<Person> *stack) {
        wcout << L"Stack size = " <<stack-> data->getLength() << endl;
        for (int i = 0; i <stack-> data->getLength(); i++) {
            wcout <<L"ID: "<<stack-> data->get(i).GetID().id<< L" Фамилия: "<<stack-> data->get(i).GetLastName() << L" Имя: "<<stack-> data->get(i).GetFirstName() << L" Отчество: "<<stack-> data->get(i).GetMiddleName() << L"| ";
        }
        wcout << endl;
    }
    void print(Stack<FunctionHolder> *stack) {
        wcout << L"Stack size = " <<stack-> data->getLength() << endl;
        wprintf(L"Введите два целых числа: ");
        int a, b;
        wcin >> a >> b;
        for (int i = 0; i <stack-> data->getLength(); i++) {
            wcout << L"Результат функции " << stack->data->get(i).name
                  << L": " << to_wstring((stack->data->get(i).funcPtr)(a, b)) << L"| ";
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

    explicit Stack(Sequence<T> *sequence, const wchar_t *string) : data(sequence) {
        wcout << string << endl;
        int N;
        wprintf(L"Введите количество элементов: ");
        wcin >> N;
        for (int i = 0; i < N; i++) {
            wprintf(L"Ввод элемента с индексом %d ", i);
            T element;
            filldata(&element);  // Заполняем элемент()
            push(element);  // Добавляем его на вершину стека

        }

    }

    Sequence<T> *getSubsequence(int startIndex, int endIndex) const {
        return data->getSubsequence(startIndex, endIndex);
    }
    int findSubsequence(Stack<T> &stack) {
        return data->findSubsequence(*stack.data);
    }
};


#endif  // STACK_INCLUDED

