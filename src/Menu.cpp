#ifndef PROJECT_AED_PT2_MENU_CPP
#define PROJECT_AED_PT2_MENU_CPP

#include "Menu.h"

using namespace std;

Menu::Menu() {
    this->menuState.push(MAIN_MENU);
    getMenu();
}

void Menu::getMenu() {

    if (!menuState.empty()) {
        switch(menuState.top()) {
            case 0: mainMenu(); break;
        }
    } else exit(0);
}

void Menu::mainMenu() {

    int option;
    do {
        cout << "=================STCP==================" << endl;
        cout << "=======================================" << endl;
        cout << "1 - Encontrar rota" << endl;
        cout << "2 - Sair" << endl;
        cout << "Escolha: ";
        cin >> option;
        cout << "=======================================" << endl;
        if (option < 1 || option > 3) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');

    } while (option < 1 || option > 3);

    switch (option) {
    }
    getMenu();
}

void Menu::routeTypeMenu() {
    int
}

#endif // PROJECT_AED_PT2_MENU_CPP