#ifndef PROJECT_AED_PT2_MENU_H
#define PROJECT_AED_PT2_MENU_H

#include <iostream>
#include <stack>

#define MAIN_MENU 0
#define ROUTE_TYPE_MENU 1

class Menu {

private:

    /**
     * @var option - user menu option
     */
    int option;

    /**
     * @var menuState - stack used to navigate through the menu
     * */
    std::stack<short int> menuState;

    /**
     * Function that calls the top of the menuState stack
     * */
    void getMenu();



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
};

#endif // PROJECT_AED_PT2_MENU_H