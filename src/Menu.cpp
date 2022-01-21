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
            coordTypeMenu();
            break;
        case 2:
            menuState.pop();
            break;
    }
    getMenu();
}

void Menu::coordTypeMenu() {
    cout << "==========Encontrar rota=============" << endl;
    cout << "1 - Menu Coordenadas" << endl;
    cout << "2 - Menu Paragens" << endl;
    cout << "3 - Menu Zonas" << endl;
    cout << "4 - Ir para o menu anterior" << endl;
    cout << "Escolha: ";
    cin >> option;
}

void Menu::routeTypeMenu() {
    do {
        cout << "=============Tipos de Rota=============" << endl;
        cout << "=======================================" << endl;
        cout << "1 - Passando por menos paragens" << endl;
        cout << "2 - Percorrendo menor distância" << endl;
        cout << "3 - Mudar de autocarro mínimas vezes" << endl;
        cout << "4 - Percurso mais barato" << endl;
        cout << "5 - Voltar ao menu principal" << endl;
        cout << "Escolha: ";
        cin >> option;
        cout << "=======================================" << endl;
        if (option < 1 || option > 5) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');

    } while (option < 1 || option > 3);

    switch (option) {
    }
    getMenu();
}

#endif // PROJECT_AED_PT2_MENU_CPP