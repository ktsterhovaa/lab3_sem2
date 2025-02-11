#ifndef LAB3_FUNCTIONHOLDER_H
#define LAB3_FUNCTIONHOLDER_H

typedef int (*FunctionPointer)(int, int);

// Структура для хранения указателя на функцию
struct FunctionHolder {
    FunctionPointer funcPtr;
    wstring name;
};


#endif //LAB3_FUNCTIONHOLDER_H
