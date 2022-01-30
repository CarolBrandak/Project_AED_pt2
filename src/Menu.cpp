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
            case 5: searchDefinitionsMenu(); break;
        }
    } else exit(0);
}

void Menu::mainMenu() {

    do {
        cout << "=================STCP==================" << endl;
        cout << "=======================================" << endl;
        cout << "1 - Encontrar rota" << endl;
        cout << "2 - Definicoes de procura" << endl;
        cout << "3 - Sair" << endl;
        cout << "Escolha: ";
        cin >> option;
        cout << "=======================================" << endl;
        if (option < 1 || option > 3) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');

    } while (option < 1 || option > 3);

    switch (option) {
        case 1:
            menuState.push(ROUTE_TYPE_MENU);
            break;
        case 2:
            menuState.push(SEARCH_DEFINITIONS_MENU);
            break;
        case 3: default:
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
        cout << "2 - Percorrendo menor distancia" << endl;
        cout << "3 - Mudar de autocarro minimas vezes" << endl;
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

void Menu::searchDefinitionsMenu() {
    do {
        cout << "=============Definicoes de Procura=============" << endl;
        cout << "===============================================" << endl;
        cout << "1 - Desativar 1 ou mais paragens" << endl;
        cout << "2 - Desativar 1 ou mais linhas" << endl;
        cout << "3 - Desativar 1 ou mais zonas" << endl;
        cout << "4 - Desativar uma area especifica" << endl;
        cout << "5 - Ativar todas paragens" << endl;
        cout << "6 - Voltar ao menu anterior" << endl;
        cout << "Escolha: ";
        cin >> option;
        cout << "===============================================" << endl;
        if (option < 1 || option > 6) cout << "Erro, por favor tente novamente!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');

    } while (option < 1 || option > 6);

    switch (option) {
            case 1: disableBusStopMenu(); break;
            case 2: disableBusLineMenu(); break;
            case 3: disableZoneMenu(); break;
            case 4: disableAreaMenu(); break;
            case 5: stcp.activateAllStops(); cout << "Todas as paragens foram ativadas!" << endl; break;
            case 6: menuState.pop(); break;
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

    double departureNorth, departureWest,
           arrivalNorth, arrivalWest;
    cout << "Insira as coordenadas de onde quer partir" << endl;
    cout << "Coordenada Norte: ";
    cin >> departureNorth;
    cout << "Coordenada Oeste: ";
    cin >> departureWest;

    cout << "Insira as coordenadas do destino" << endl;
    cout << "Coordenada Norte: ";
    cin >> arrivalNorth;
    cout << "Coordenada Oeste: ";
    cin >> arrivalWest;

    Coordinate departureCoordinate = {departureNorth, departureWest};
    Coordinate arrivalCoordinate = {arrivalNorth,arrivalWest};
    stcp.createFootItineraries(footInputMenu());
    stcp.showPath(departureCoordinate,arrivalCoordinate,optionType);
    menuState.pop();
    menuState.pop();
    getMenu();
}

void Menu::stopInputMenu() {
    string departureStop, arrivalStop;
    cout << "Insira o codigo da paragem de onde quer partir: ";
    cin >> departureStop;
    cout << "Insira o codigo da paragem destino: ";
    cin >> arrivalStop;
    stcp.createFootItineraries(footInputMenu());
    stcp.showPath(departureStop,arrivalStop,optionType);
    menuState.pop();
    menuState.pop();
    getMenu();
}

void Menu::disableBusStopMenu() {
    bool insert = false; string name;
    while (!insert) {
        cout << "Insira o codigo da paragem:" << endl;
        cin >> name;
        stcp.disableStop(name);
        cout << "Deseja desativar outra paragem? (S - Sim, N - Nao):" << endl;
        cin >> name;
        if (name == "N" || name == "n") insert = true;
    }
}

void Menu::disableBusLineMenu() {
    bool insert = false; string name;
    while (!insert) {
        cout << "Insira o codigo da linha:" << endl;
        cin >> name;
        stcp.disableLine(name);
        cout << "Deseja desativar outra linha? (S - Sim, N - Nao):" << endl;
        cin >> name;
        if (name == "N" || name == "n") insert = true;
    }
}

void Menu::disableZoneMenu() {
    bool insert = false; string name;
    while (!insert) {
        cout << "Insira o codigo da zona:" << endl;
        cin >> name;
        stcp.disableZone(name);
        cout << "Deseja desativar outra zona? (S - Sim, N - Nao):" << endl;
        cin >> name;
        if (name == "N" || name == "n") insert = true;
    }
}

void Menu::disableAreaMenu() {
    double distance; string name,stop;
    bool pass = false;
    do {
        cout << "Quer desativar a partir de uma paragem ou coordenada? (P - Paragem, C - Coordenada):" << endl;
        cin >> name;
        if (name == "P" || name == "p") {
            cout << "Insira o codigo da paragem: " << endl;
            cin >> stop;
            cout << "Qual a quantidade de metros limite para desativar? " << endl;
            cin >> distance;
            stcp.disableArea(stop, distance);
            pass = true;
        } else if (name == "C" || name == "c") {
            double latitude, longitude;
            cout << "Insira as coordenadas de onde quer partir:" << endl;
            cout << "Coordenada Norte: ";
            cin >> latitude;
            cout << "Coordenada Oeste: ";
            cin >> longitude;
            cout << "Qual a quantidade de metros limite para desativar? " << endl;
            cin >> distance;
            Coordinate coordinate = {latitude, longitude};
            stcp.disableArea(coordinate, distance);
            pass = true;
        }
        cin.clear();
        cin.ignore(1000, '\n');
    } while (!pass);
    getMenu();
}

double Menu::footInputMenu() {
    double footMeters;
    cout << "Qual e a quantidade de metros que esta disposto a andar a pe? ";
    cin >> footMeters;
    return footMeters;
}

#endif // PROJECT_AED_PT2_MENU_CPP