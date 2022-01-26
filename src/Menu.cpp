#ifndef PROJECT_AED_PT2_MENU_CPP
#define PROJECT_AED_PT2_MENU_CPP

#include "Menu.h"

using namespace std;

Menu::Menu() {
    this->menuState.push(MAIN_MENU);
    stcp = STCP();
    getMenu();
}

void Menu::getMenu() {

    if (!menuState.empty()) {
        switch(menuState.top()) {
            case 0: mainMenu(); break;
            case 1: routeTypeMenu(); break;
            case 2: coordTypeMenu(); break;
            case 3: coordInputMenu(); break;
            case 4: stopInputMenu(); break;
            case 5: footInputMenu(); break;
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
        if (option < 1 || option > 2) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');

    } while (option < 1 || option > 3);

    switch (option) {
        case 1:
            menuState.push(ROUTE_TYPE_MENU);
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
        cin >> optionType;
        cout << "=======================================" << endl;
        if (optionType < 1 || optionType > 5) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');

    } while (optionType < 1 || optionType > 5);

    switch (optionType) {
        case 1: case 2: case 3: case 4:
            menuState.push(COORD_TYPE_MENU);
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
        cin >> optionCoord;
        cout << "=======================================" << endl;
        if (optionCoord < 1 || optionCoord > 3) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (optionCoord < 1 || optionCoord > 3);

    switch (optionCoord) {
        case 1:
            menuState.push(COORDINATE_MENU);
            break;
        case 2:
            menuState.push(STOP_MENU);
            break;
        case 3:
            menuState.pop();
            break;
    }
    getMenu();
}


void Menu::coordInputMenu() {

    double n, w;
    cout << "Coordenada Norte ";
    cin >> n;
    cout << "Coordenada Oeste: ";
    cin >> w;
    Coordinate c = {n, w};
    Node stop = stcp.getStop(c);
}

void Menu::stopInputMenu() {


}

int Menu::footInputMenu() {



    return;
}

#endif // PROJECT_AED_PT2_MENU_CPP