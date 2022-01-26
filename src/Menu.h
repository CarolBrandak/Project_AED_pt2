#ifndef PROJECT_AED_PT2_MENU_H
#define PROJECT_AED_PT2_MENU_H

#include "STCP.h"
#include <iostream>
#include <stack>

#define MAIN_MENU 0
#define ROUTE_TYPE_MENU 1
#define COORD_TYPE_MENU 2
#define COORDINATE_MENU 3
#define STOP_MENU 4
#define FOOT_MENU 5

class Menu {

private:

    /**
     * @var option - user menu option
     */

    int optionType;

    int option;

    /**
     * @var menuState - stack used to navigate through the menu
     * */
    std::stack<short int> menuState;

    /**
     * Function that calls the top of the menuState stack
     * */
    void getMenu();

    STCP stcp;

public:

    /**
     * Constructor for the menu class
     * */
    Menu();

    /**
     * Main menu that allows the user to choose
     * between the find route menu or leave the
     * program
     * */
    void mainMenu();

    /**
     * Menu that allows user to choose the type
     * of route he would like to check
     */
     void routeTypeMenu();

    void coordTypeMenu();

    void coordInputMenu();

    void stopInputMenu();

    double footInputMenu();
};

#endif // PROJECT_AED_PT2_MENU_H