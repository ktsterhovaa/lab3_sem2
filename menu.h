#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <cassert>
#include <cwchar>
#include <iostream>

struct MenuItem {
    const wchar_t *name;

    void (*f)();
};

void menuLoop(const wchar_t *title, int N, MenuItem menu[]) {

    while (true) {
        wprintf(L"%ls (0 - выход):\n", title);  // Печатаем заголовок меню ls - строчка в формате юникод

        // Печатаем меню
        for (int no = 1; no <= N; no++) {  // no=1,2,3...N - номер пункта меню
            wprintf(L"  %d. %ls\n", no, menu[no - 1].name);
        }

        // Печатаем предложение о выборе
        wprintf(L"Выберите (1..%d): ", N);
        int choice;  // Выбор пользователя
        wcin >> choice;
        if (choice >= 1 && choice <= N) {
            int index = choice - 1;
            std::wcout << L"Вы выбрали: " << menu[index].name << std::endl;
            menu[index].f();  // Вызываем функцию
            std::wcout << std::endl;
        } else if (choice == 0) {
            wprintf(L"Выбран %d => выход\n", choice);
            return;
        } else {
            wprintf(L"Пункта меню %d нет => повторите выбор\n", choice);
        }
    }
}

#endif
