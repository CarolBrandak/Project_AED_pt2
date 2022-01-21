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
        case 1:
            routeTypeMenu();
            break;
        case 2:
            menuState.pop();
            break;
    }
    getMenu();
}

void Menu::routeTypeMenu() {
    do {
        cout << "=============Tipos de Rota=============" << endl;
        cout << "=======================================" << endl;
        cout << "1 - Passando por menos paragens" << endl;
        cout << "2 - Percorrendo menor distância" << endl;
        cout << "3 - Mudar de autocarro mínimas vezes" << endl;
        cout << "4 - Percurso mais barato" << endl;
        cout << "5 - Voltar ao menu anterior" << endl;
        cout << "Escolha: ";
        cin >> option;
        cout << "=======================================" << endl;
        if (option < 1 || option > 5) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');

    } while (option < 1 || option > 5);

    switch (option) {
        case 1:
            coordTypeMenu();
            break;
        case 2:
            coordTypeMenu();
            break;
        case 3:
            coordTypeMenu();
            break;
        case 4:
            coordTypeMenu();

            break;
        case 5:
            menuState.pop();
    }
    getMenu();
}
void Menu::coordTypeMenu() {
    do{
        cout << "==========Encontrar rota=============" << endl;
        cout << "1 - Por Coordenadas?" << endl;
        cout << "2 - Por Paragens?" << endl;
        cout << "3 - Voltar ao menu principal" << endl;
        cout << "Escolha: ";
        cin >> option;
        cout << "=======================================" << endl;
        if (option < 1 || option > 3) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (option < 1 || option > 3);

    switch (option) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            menuState.pop();
            break;
    }
    getMenu();
}
#endif // PROJECT_AED_PT2_MENU_CPP