// Консольная программа для демонстрации

#include <fcntl.h>

#include <chrono>
#include <complex>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <fstream>

#include "arraysequence.h"
#include "Common.h"
#include "linkedlist.h"
#include "linkedlistsequence.h"
#include "menu.h"
#include "Stack.h"
#include "CString.h"
#include "deque.h"
#include "queue.h"
#include "Person.h"
#include "FunctionHolder.h"
#include "SegmentedDeque.h"
#include "Functions.h"




//functions of printing
template<class T>
void print_sequence(Sequence<T> *sequence) {
    for (int i = 0; i < sequence->getLength(); i++) {
        wcout << sequence->get(i) << L" ";
    }
    wcout << endl;
}
void print_sequence(Sequence<Person> *sequence) {
    wcout << L"size = " <<sequence->getLength() << endl;
    for (int i = 0; i <sequence->getLength(); i++) {
        wcout <<L"ID: "<<sequence->get(i).GetID().id<< L" Фамилия: "<<sequence-> get(i).GetLastName() << L" Имя: "<<sequence->get(i).GetFirstName() << L" Отчество: "<<sequence->get(i).GetMiddleName() << L"| ";
    }
    wcout << endl;
}
void print_sequence(Sequence<FunctionHolder> *sequence) {
    wcout << L"size = " <<sequence->getLength() << endl;
    wprintf(L"Ввеите два целых числа: ");
    int a, b;
    wcin >> a >> b;
    for (int i = 0; i <sequence->getLength(); i++) {
        wcout <<L"Функция "<<sequence->get(i).name<<L" Результат: " <<(sequence->get(i).funcPtr)(a, b)<< L"| ";
    }
    wcout << endl;
}
// Функиия, которую можно применить к каждому элементу последовательности
template<class T>
T map_function(T x) {
    return x * x;
}

wstring map_function(wstring x) { return x + L"!"; }

Person map_function(Person x) {
    Person person;
    person.SetFirstName(x.GetFirstName() + L" " + x.GetLastName() + L" " + L" " + x.GetMiddleName() + L" " +
                        to_wstring(x.GetID().id));
    return person;
}
FunctionHolder map_function(FunctionHolder x) {
    Functions functions;
    FunctionHolder holder;
    wstring name = x.name;
    if (name==L"Сложение") {
        holder.name = L"Вычитание";
        holder.funcPtr =&functions.Sub;
    }else if (name==L"Вычитание") {
        holder.name = L"Сложение";
        holder.funcPtr =&functions.Add;
    }
    return holder;
}

// Фильтры для разных типов данных. Для каждого типа - своя
bool where_function(int x) {
    bool result = (x % 2) == 0;
    wcout << L"  where: число " << x << L" чётное: " << result << endl;
    return result;
}

bool where_function(double x) {
    bool result = abs(x) < 5;
    wcout << L"  where: число |" << x << L"| < 5: " << result << endl;
    return result;
}

bool where_function(complex<double> x) {
    bool result = abs(x) < 5;
    wcout << L"  where: число |" << x << L"| < 5: " << result << endl;
    return result;
}

bool where_function(const wstring x) {
    bool result = x.size() < 4;
    wcout << L"  where: длина строки " << x << L" < 4: " << result << endl;
    return result;
}

bool where_function(Person x) {
    bool result = x.GetID().id < 4;
    wcout << L"  where: значение Id " << x.GetID().id << L" < 4: " << result << endl;
    return result;
}
bool where_function(FunctionHolder x) {
    bool result = x.name ==L"Сложение";
    wcout << L"  where: Сложение ли? " << x.name << L" == Сложение: " << result << endl;
    return result;
}

// Сложение для всех чисел (конкатенация для строк)
template<class T>
T reduce_function(T a, T b) {
    T result = a + b;
    wcout << L"  reduce: " << a << L" + " << b << " = " << result << endl;
    return result;
}

Person reduce_function(Person a, Person b) {
    Person result;
    result.SetID(a.GetID().id + b.GetID().id);
    result.SetFirstName(a.GetFirstName() + b.GetFirstName());
    wcout << L"  reduce: " << a.GetFirstName() << L" + " << b.GetFirstName() << " = " << result.GetFirstName()<< endl;
    return result;
}
FunctionHolder reduce_function(FunctionHolder a, FunctionHolder b) {
    FunctionHolder result;
    result.name = a.name;
    result.funcPtr = b.funcPtr;
    wcout << L"  reduce: " << a.name<< L" + " << b.name << " = " << result.name<< endl;
    return result;
}
//Stack
template<class T>
void apply_map_where_reduce_stack() {
    wprintf(L"Применение функций map, where, reduce - ручной ввод данных\n");
    Stack<T> stack(new LinkedListSequence<T>, L"Ввод элементов первого стека");
    wprintf(L"Введенный стек: \n");
    stack.print(&stack);
    wprintf(L"Применяем операцию map\n");
    Stack<T> *mapRes = stack.map(map_function);
    mapRes->print(mapRes);
    delete mapRes;    // Очищаем память

    wprintf(L"Применяем операцию where\n");
    Stack<T> *whereRes = stack.where(where_function);
    whereRes->print(whereRes);
    delete whereRes;  // Очищаем память

    wprintf(L"Применяем операцию reduce - сложение для всех чисел (конкатенация для строк)\n");
    T reduceRes = stack.reduce(reduce_function);

    wprintf(L"\n");
}

template<class T>
void stack_concat() {
    wprintf(L"Конкатенация двух стеков\n");

    try {
        Stack<T> stack1(new LinkedListSequence<T>, L"Ввод элементов первого стека");
        Stack<T> stack2(new LinkedListSequence<T>, L"Ввод элементов второго стека");

        wprintf(L"Введенные стеки: \n");
        stack1.print(&stack1);
        stack2.print(&stack2);
        wprintf(L"Результат конкатенации: \n");
        Stack<T> *result = stack1.concat(stack2);
        result->print(result);
        delete result;

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void stack_getSubSequence() {
    wprintf(L"Извлечение подпоследовательности (по заданным индексам)\n");
    try {
        Stack<T> stack(new LinkedListSequence<T>, L"Ввод элементов стека");
        wcout << L"Введите начальный индекс: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Введите конечный индекс: ";
        int endIndex;
        wcin >> endIndex;
        wprintf(L"Введенный стек: \n");
        stack.print(&stack);
        wprintf(L"Результат извлечения подпоследовательности:\n");
        Sequence<T> *result = stack.getSubsequence(startIndex, endIndex);
        print_sequence(result);
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void stack_findSubSequence() {
    wprintf(L"Поиск на вхождение подпоследовательности\n");

    try {
        LinkedListSequence<T> linkedListSequence;
        Stack<T> stack(new LinkedListSequence<T>, L"Ввод элементов стека");
        Stack<T> subSequence(new LinkedListSequence<T>, L"Ввод подпоследовательности");

        wprintf(L"Введенная последовательность: \n");
        stack.print(&stack);
        wprintf(L"Введенная подпоследовательность: \n");
        subSequence.print(&subSequence);
        int index = stack.findSubsequence(subSequence);
        wcout << L"Позиция подпоследовательности = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

// Замеряем время работы стека
void stackImplementationSpeed(Sequence<int> *sequence) {
    auto begin = chrono::steady_clock::now();  // Засекаем начало работы

    Stack<int> stack(sequence);  // Создаём стек
    const int numbers = 20000;   // Добавим числа
    wcout << L"Количество элементов для тестирования: " << numbers << endl;
    for (int i = 1; i <= numbers; i++) {
        stack.push(i);
    }

    auto end = chrono::steady_clock::now();  // Конец работы
    auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - begin);
    // Вычисляем разницу в секундах времени начала и окончания работы
    const double t = elapsed_mcs.count() / 1e6;
    // Выводим результат в секундах на экран (в консоль)
    wcout << typeid(stack).name() << " time = " << t << endl;
}

template<class T>
void stack_addElementSpeed() {
    wprintf(L"Сравнение времени добавления элементов в стек на основе LinkedList и DynamicArray\n");
    stackImplementationSpeed(new LinkedListSequence<int>());
    stackImplementationSpeed(new ArraySequence<int>());
}

//Queue
template<class T>
void apply_map_where_reduce_queue() {
    wprintf(L"Применение функций map, where, reduce - ручной ввод данных\n");

    Queue<T> queue(new LinkedListSequence<T>, L"Ввод данных очереди");
    wprintf(L"Введенная очередь: \n");
    queue.print(&queue);
    wprintf(L"Применяем операцию map\n");
    Queue<T> *mapRes = queue.map(map_function);
    mapRes->print(mapRes);  // Печатаем содержимое стека
    delete mapRes;    // Очищаем память

    wprintf(L"Применяем операцию where\n");
    Queue<T> *whereRes = queue.where(where_function);
    whereRes->print(whereRes);
    delete whereRes;  // Очищаем память

    wprintf(L"Применяем операцию reduce - сложение для всех чисел (конкатенация для строк)\n");
    T reduceRes = queue.reduce(reduce_function);

    wprintf(L"\n");
}

template<class T>
void queue_concat() {
    wprintf(L"Конкатенация двух очередей\n");

    try {
        Queue<T> queue1(new LinkedListSequence<T>, L"Ввод элементов первой очереди");
        Queue<T> queue2(new LinkedListSequence<T>, L"Ввод элементов второй очереди");

        wprintf(L"Введенные очереди: \n");
        queue1.print(&queue1);
        queue2.print(&queue2);
        wprintf(L"Результат конкатенации: \n");
        Queue<T> *result = queue1.concat(queue2);
        result->print(result);
        delete result;

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void queue_getSubSequence() {
    wprintf(L"Извлечение подпоследовательности (по заданным индексам)\n");
    try {
        Queue<T> queue(new LinkedListSequence<T>, L"Ввод элементов очереди");
        wcout << L"Введенная очередь: \n";
        queue.print(&queue);
        wcout << L"Введите начальный индекс: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Введите конечный индекс: ";
        int endIndex;
        wcin >> endIndex;
        wprintf(L"Результат извлечения подпоследовательности: \n");
        Sequence<T> *result = queue.getSubsequence(startIndex, endIndex);
        print_sequence(result);
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void queue_findSubSequence() {
    wprintf(L"Поиск на вхождение подпоследовательности\n");

    try {
        LinkedListSequence<T> linkedListSequence;
        Queue<T> queue(new LinkedListSequence<T>, L"Ввод элементов очереди");
        Queue<T> subSequence(new LinkedListSequence<T>, L"Ввод подпоследовательности");
        wprintf(L"Введенная очередь: \n");
        queue.print(&queue);
        wprintf(L"Введенная подпоследовательность: \n");
        subSequence.print(&subSequence);
        int index = queue.findSubsequence(subSequence);
        wcout << L"Позиция подполедовательности = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

// Замеряем время работы стека
void queueImplementationSpeed(Sequence<int> *sequence) {
    auto begin = chrono::steady_clock::now();  // Засекаем начало работы

    Queue<int> queue(sequence);  // Создаём стек
    const int numbers = 20000;   // Добавим числа
    wcout << L"Количество элементов для тестирования: " << numbers << endl;
    for (int i = 1; i <= numbers; i++) {
        queue.enqueue(i);
    }

    auto end = chrono::steady_clock::now();  // Конец работы
    auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - begin);
    // Вычисляем разницу в секундах времени начала и окончания работы
    const double t = elapsed_mcs.count() / 1e6;
    // Выводим результат в секундах на экран (в консоль)
    wcout << typeid(queue).name() << " time = " << t << endl;
}

template<class T>
void queue_addElementSpeed() {
    wprintf(L"Сравнение времени добавления элементов в очередь на основе LinkedList и DynamicArray\n");
    queueImplementationSpeed(new LinkedListSequence<int>());
    queueImplementationSpeed(new ArraySequence<int>());
}


//Deque
template<class T>
void apply_map_where_reduce_deque() {
    wprintf(L"Применение функций map, where, reduce - ручной ввод данных\n");

    Deque<T> deque(new LinkedListSequence<T>, L"Ввод данных дека");

    wprintf(L"Введенный дек: \n");
    deque.print(&deque);
    wprintf(L"Применяем операцию map\n");
    Deque<T> *mapRes = deque.map(map_function);
    mapRes->print(mapRes);  // Печатаем содержимое стека
    delete mapRes;    // Очищаем память

    wprintf(L"Применяем операцию where\n");
    Deque<T> *whereRes = deque.where(where_function);
    whereRes->print(whereRes);
    delete whereRes;  // Очищаем память

    wprintf(L"Применяем операцию reduce - сложение для всех чисел (конкатенация для строк)\n");
    T reduceRes = deque.reduce(reduce_function);

    wprintf(L"\n");
}

template<class T>
void deque_concat() {
    wprintf(L"Конкатенация двух деков\n");

    try {
        Deque<T> deque1(new LinkedListSequence<T>, L"Ввод элементов первого дека");
        Deque<T> deque2(new LinkedListSequence<T>, L"Ввод элементов второго дека");

        wprintf(L"Введенные деки: \n");
        deque1.print(&deque1);
        deque2.print(&deque2);
        wprintf(L"Результат конкатенации: \n");
        Deque<T> *result = deque1.concat(deque2);
        result->print(result);
        delete result;

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void deque_getSubSequence() {
    wprintf(L"Извлечение подпоследовательности (по заданным индексам)\n");
    try {
        Deque<T> deque(new LinkedListSequence<T>, L"Ввод элементов дека");
        wcout << L"Введите начальный индекс: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Введите конечный индекс: ";
        int endIndex;
        wcin >> endIndex;

        wprintf(L"Введенный дек: \n");
        deque.print(&deque);
        wprintf(L"Результат извлечения подпоследовательности: \n");
        Sequence<T> *result = deque.getSubsequence(startIndex, endIndex);
        print_sequence(result);
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void deque_findSubSequence() {
    wprintf(L"Поиск на вхождение подпоследовательности\n");

    try {
        LinkedListSequence<T> linkedListSequence;
        Deque<T> deque(new LinkedListSequence<T>, L"Ввод элементов дека");
        Deque<T> subSequence(new LinkedListSequence<T>, L"Ввод подпоследовательности");

        wprintf(L"Введенный дек: \n");
        deque.print(&deque);
        wprintf(L"Введенная подпоследовательность: \n");
        subSequence.print(&subSequence);
        int index = deque.findSubsequence(subSequence);
        wcout << L"Позиция подпоследовательности = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

// Замеряем время работы стека
void dequeImplementationSpeed(Sequence<int> *sequence) {
    auto begin = chrono::steady_clock::now();  // Засекаем начало работы

    Deque<int> deque(sequence);  // Создаём стек
    const int numbers = 20000;   // Добавим числа
    wcout << L"Количество элементов для тестирования: " << numbers << endl;
    for (int i = 1; i <= numbers; i++) {
        deque.pushFront(i);
    }

    auto end = chrono::steady_clock::now();  // Конец работы
    auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - begin);
    // Вычисляем разницу в секундах времени начала и окончания работы
    const double t = elapsed_mcs.count() / 1e6;
    // Выводим результат в секундах на экран (в консоль)
    wcout << typeid(deque).name() << " time = " << t << endl;
}

template<class T>
void deque_addElementSpeed() {
    wprintf(L"Сравнение времени добавления элементов в дек на основе LinkedList и DynamicArray\n");
    dequeImplementationSpeed(new LinkedListSequence<int>());
    dequeImplementationSpeed(new ArraySequence<int>());
}

//Segmented deque

template<class T>
void deque_segmented_basic_operations() {
    wprintf(L"Базовые операции сегментированного дека\n");
    int n;
    wcout << L"Введите количество элементов в одном сегменте: ";
    wcin >> n;
    try {
        SegmentedDeque<T> deque1(n, L"Ввод элементов дека");
        deque1.print(&deque1);
        wprintf(L"Сколько элементов будет удалено: ");
        int k;
        wcin >> k;
        for (int i = 0; i < k; i++) {
            wprintf(L"Введите 1, если хотите удалить элемент с начала, 0, если с конца: ");
            int where;
            wcin >> where;
            if (where==1) {
                deque1.popFront();
                deque1.print(&deque1);
            }else if(where==0) {
                deque1.popBack();
                deque1.print(&deque1);
            }else{
                wcout << L"Неверно введено значение" << endl;
            }
        }
        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

//Cstring

template<class T>
void cstring_concat() {
    wprintf(L"Конкатенация двух строк\n");

    try {
        CString<T> cString1(new LinkedListSequence<T>, L"Ввод элементов первой строки");
        CString<T> cString2(new LinkedListSequence<T>, L"Ввод элементов второй строки");

        wprintf(L"Введенные строки: \n");
        cString1.print();
        cString2.print();
        wprintf(L"Результат конкатенации: \n");
        CString<T> *result = cString1.concat(cString2);
        result->print();
        delete result;

        wprintf(L"\n");
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void cstring_getSubSequence() {
    wprintf(L"Извлечение подпоследовательности (по заданным индексам)\n");
    try {
        CString<T> cString(new LinkedListSequence<T>, L"Ввод элементов строки");
        wcout << L"Введите начальный индекс: ";
        int startIndex;
        wcin >> startIndex;
        wcout << L"Введите конечный индекс: ";
        int endIndex;
        wcin >> endIndex;

        wprintf(L"Введенная строка: \n");
        cString.print();
        wprintf(L"Результат извлеченная подпоследовательность: \n");
        Sequence<T> *result = cString.getSubsequence(startIndex, endIndex);
        print_sequence(result);
        delete result;

        wcout << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}

template<class T>
void cstring_findSubSequence() {
    wprintf(L"Поиск на вхождение подпоследовательности\n");

    try {
        CString<T> cString(new LinkedListSequence<T>, L"Ввод элементов строки");
        CString<T> subSequence(new LinkedListSequence<T>, L"Ввод подпоследовательности");
        wprintf(L"Введенная строка: \n");
        cString.print();
        wprintf(L"Введенная подстрока: \n");
        subSequence.print();
        int index = cString.findSubsequence(subSequence);
        wcout << L"Позиция подпоследовательности = " << index << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}
template<class T>
void cstring_equal() {
    wprintf(L"Равенство строк\n");

    try {
        CString<T> cString1(new LinkedListSequence<T>, L"Ввод элементов 1 строки");
        CString<T> cString2(new LinkedListSequence<T>, L"Ввод элементов 2 строки");

        wprintf(L"Введенные строки: \n");
        cString1.print();
        cString2.print();
        bool result = cString1.equals(cString1, cString2);
        wcout << L"Равны ли строки? " << result << endl << endl;
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}
template<class T>
void cstring_devide() {
    wprintf(L"Разбиение строки на подстроки\n");
    wprintf(L"Введите количество индексов с которых будут выделены подстроки: ");
    int N;
    wcin >> N;
    int data[N];
    for (int i = 0; i < N; i++) {
        wprintf(L"Введите %d индекс : ", i);
        wcin >> data[i];
    }
    try {
        CString<T> cString(new LinkedListSequence<T>, L"Ввод элементов строки");
        wprintf(L"Введенная строка: \n");
        cString.print();
        wprintf(L"Результат разбиения: \n");
        CString<T>(cString.getSubsequence(0, data[0])).print();
        for (int i = 0; i < N; i++) {
            CString<T>(cString.getSubsequence(data[i], data[i + 1])).print();
        }
        CString<T>(cString.getSubsequence(data[N - 1], cString.getLength() - 1)).print();
        wcout << endl;
    }
    catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }

}

template<class T>
void cstring_change() {
    wprintf(L"Изменение подстрок\n");
    try {
        CString<T> cString(new LinkedListSequence<T>, L"Ввод элементов строки в которой будет изменена подстрока");
        wprintf(L"Введенная строка: \n");
        cString.print();
        CString<T> subSequence(new LinkedListSequence<T>, L"Ввод строки для изменения");
        wprintf(L"Введенная подстрока: \n");
        subSequence.print();
        wprintf(L"Введите индексы между которыми будет изменена подстрока: ");
        int data[2];
        for (int i = 0; i < 2; i++) {
            wprintf(L"Введите %d индекс : ", i);
            wcin >> data[i];
        }
        wprintf(L"Результат изменения: \n");
        CString<T> part1(cString.getSubsequence(0, data[0]));
        CString<T> part2(cString.getSubsequence(data[1], cString.getLength() - 1));
        CString<T> *result = (part1.concat(subSequence))->concat(part2);
        result->print();
        delete result;
        wcout << endl;
    }
    catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }

}
void cstringImplementationSpeed(Sequence<wchar_t> *sequence) {
    auto begin = chrono::steady_clock::now();  // Засекаем начало работы

    CString<wchar_t> cString(sequence);  // Создаём стек
    const int numbers = 20000;   // Добавим числа
    wcout << L"Количество элементов для тестирования: " << numbers << endl;
    for (int i = 1; i <= numbers; i++) {
        cString.push(wchar_t(i));  // Добавляем элемент с индексом i);
    }

    auto end = chrono::steady_clock::now();  // Конец работы
    auto elapsed_mcs = chrono::duration_cast<chrono::microseconds>(end - begin);
    // Вычисляем разницу в секундах времени начала и окончания работы
    const double t = elapsed_mcs.count() / 1e6;
    // Выводим результат в секундах на экран (в консоль)
    wcout << typeid(cString).name() << " time = " << t << endl;
}

template<class T>
void cstring_addElementSpeed() {
    wprintf(L"Сравнение времени добавления элементов в стек на основе LinkedList и DynamicArray\n");
    cstringImplementationSpeed(new LinkedListSequence<wchar_t>());
    cstringImplementationSpeed(new ArraySequence<wchar_t>());
}

// Главное меню

template<class T>
void main_menu_stack() {
    MenuItem menu_stack[] = {
            {L"Применение функции map, where, reduce - ручной ввод данных",                        apply_map_where_reduce_stack<T>},
            {L"Конкатенация двух стеков",                                                          stack_concat<T>},
            {L"Извлечение подпоследовательности (по заданным индексам)",                           stack_getSubSequence<T>},
            {L"Поиск на вхождение подпоследовательности",                                          stack_findSubSequence<T>},
            {L"Сравнение времени добавления элементов в стек на основе LinkedList и DynamicArray", stack_addElementSpeed<T>}};
    menuLoop(L"Возможные операции", _countof(menu_stack), menu_stack);
}


template<class T>
void main_menu_queue() {
    MenuItem menu_queue[] = {
            {L"Применение функции map, where, reduce - ручной ввод данных",                        apply_map_where_reduce_queue<T>},
            {L"Конкатенация двух очередей",                                                          queue_concat<T>},
            {L"Извлечение подпоследовательности (по заданным индексам)",                           queue_getSubSequence<T>},
            {L"Поиск на вхождение подпоследовательности",                                          queue_findSubSequence<T>},
            {L"Сравнение времени добавления элементов в стек на основе LinkedList и DynamicArray", queue_addElementSpeed<T>}};
    menuLoop(L"Возможные операции", _countof(menu_queue), menu_queue);
}

template<class T>
void main_menu_deque() {
    MenuItem menu_deque[] = {
            {L"Применение функции map, where, reduce - ручной ввод данных",                        apply_map_where_reduce_deque<T>},
            {L"Конкатенация двух деков",                                                          deque_concat<T>},
            {L"Извлечение подпоследовательности (по заданным индексам)",                           deque_getSubSequence<T>},
            {L"Поиск на вхождение подпоследовательности",                                          deque_findSubSequence<T>},
            {L"Сравнение времени добавления элементов в стек на основе LinkedList и DynamicArray", deque_addElementSpeed<T>}};
    menuLoop(L"Возможные операции", _countof(menu_deque), menu_deque);
}

template<class T>
void main_menu_deque_segmented() {
    MenuItem menu_deque[] = {
            {L"Базовые операции",                                                                deque_segmented_basic_operations<T>}};
    menuLoop(L"Возможные операции", _countof(menu_deque), menu_deque);
}

template<class T>
void main_menu_cstring() {
    MenuItem menu_cstring[] = {
            {L"Конкатенация двух строк",                                                          cstring_concat<T>},
            {L"Извлечение подпоследовательности (по заданным индексам)",                           cstring_getSubSequence<T>},
            {L"Поиск на вхождение подпоследовательности",                                          cstring_findSubSequence<T>},
            {L"Сравнение времени добавления элементов в стек на основе LinkedList и DynamicArray", cstring_addElementSpeed<T>},
            {L"Разбиение строки", cstring_devide<T>},
            {L"Замена подстроки на строку", cstring_change<T>},
            {L"Сравнение двух строк", cstring_equal<T>}};
    menuLoop(L"Возможные операции", _countof(menu_cstring), menu_cstring);
}

void deque_menu() {
    wprintf(L"== Deque-Выберите тип данных ==\n");

    MenuItem menu_deque[] = {{L"Целые числа (int)",                   main_menu_deque<int>},
                             {L"Вещественные числа (double)",         main_menu_deque<double>},
                             {L"Комплексные числа (complex<double>)", main_menu_deque<complex<double>>},
                             {L"Строки/символы (string)",             main_menu_deque<wstring>},
                             {L"Студенты/преподаватели",              main_menu_deque<Person>},
                             {L"Функции",              main_menu_deque<FunctionHolder>}};
    menuLoop(L"Возможные операции", _countof(menu_deque), menu_deque);
}

void deque_segmented_menu() {
    wprintf(L"== Deque-Выберите тип данных ==\n");

    MenuItem menu_deque[] = {{L"Целые числа (int)",                   main_menu_deque_segmented<int>},
                             {L"Вещественные числа (double)",         main_menu_deque_segmented<double>},
                             {L"Комплексные числа (complex<double>)", main_menu_deque_segmented<complex<double>>},
                             {L"Строки/символы (string)",             main_menu_deque_segmented<wstring>},
                             {L"Студенты/преподаватели",              main_menu_deque_segmented<Person>},
                             {L"Функции",              main_menu_deque_segmented<FunctionHolder>}};
    menuLoop(L"Возможные операции", _countof(menu_deque), menu_deque);
}

void queue_menu() {
    wprintf(L"== Queue-Выберите тип данных ==\n");

    MenuItem menu_queue[] = {{L"Целые числа (int)",                   main_menu_queue<int>},
                             {L"Вещественные числа (double)",         main_menu_queue<double>},
                             {L"Комплексные числа (complex<double>)", main_menu_queue<complex<double>>},
                             {L"Строки/символы (string)",             main_menu_queue<wstring>},
                             {L"Студенты/преподаватели",              main_menu_queue<Person>},
                             {L"Функции",              main_menu_queue<FunctionHolder>}};
    menuLoop(L"Возможные операции", _countof(menu_queue), menu_queue);
}

void stack_menu() {
    wprintf(L"== Stack-Выберите тип данных ==\n");

    MenuItem menu_stack[] = {{L"Целые числа (int)",                   main_menu_stack<int>},
                             {L"Вещественные числа (double)",         main_menu_stack<double>},
                             {L"Комплексные числа (complex<double>)", main_menu_stack<complex<double>>},
                             {L"Строки/символы (string)",             main_menu_stack<wstring>},
                             {L"Студенты/преподаватели",              main_menu_stack<Person>},
                             {L"Функции",              main_menu_stack<FunctionHolder>}};
    menuLoop(L"Возможные операции", _countof(menu_stack), menu_stack);
}

void CString_menu() {
    wprintf(L"== CString-Выберите тип данных ==\n");
    MenuItem menu_cstring[] = {{L" (wchar_t)",              main_menu_cstring<wchar_t>},
                               {L"Строки/символы (string)", main_menu_cstring<wstring>}};
    menuLoop(L"Возможные операции", _countof(menu_cstring), menu_cstring);
}
// Основная программа
int main() {
    // Задаём кодировку UTF-16 для всего вывода в программе
    // Все символы и строки будут wchar_t
#if WIN32 || WIN64
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
#endif
    wprintf(L"== Тестирование операций ==\n");

    MenuItem menu[] = {{L"Стек",    stack_menu},
                       {L"Очередь", queue_menu},
                       {L"Дек",     deque_menu},
                       {L"CString", CString_menu},
                       {L"Сегментированный дек", deque_segmented_menu}};
    try {
        menuLoop(L"Выберите тип элементов", _countof(menu), menu);
    } catch (IndexOutOfRange &ex) {
        wcout << L"Exception: " << ex.what() << endl << endl;
    }
}
