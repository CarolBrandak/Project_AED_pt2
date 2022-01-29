#ifndef PROJECT_AED_PT2_MENU_H
#define PROJECT_AED_PT2_MENU_H

#include "STCP.h"
#include <iostream>
#include <stack>

/**
 * Menu's numbers
 */
#define MAIN_MENU 0
#define ROUTE_TYPE_MENU 1
#define COORD_TYPE_MENU 2
#define COORDINATE_MENU 3
#define STOP_MENU 4
#define SEARCH_DEFINITIONS_MENU 5

/**
 * Class to manage interface application
 */
class Menu {

    private:

        /**
         * @var option - user main menu option
         */
        int option;

        /**
         * @var optionType - users type route option
         */
        int optionType;

        /**
         * @var menuState - stack used to navigate through the menu
         * */
        stack<short int> menuState;

        /**
         * @var stcp - a STCP object containing the main graph and all methods to manipulate data
         */
        STCP stcp;

        /**
         * Function that calls the top of the menuState stack
         */
        void getMenu();

        /**
         * Menu that allows user to disable a zone from search
         */
        void disableZoneMenu();

        /**
         * Menu that allows user to disable a bus stop from search
         */
        void disableBusStopMenu();

        /**
         * Menu that allows user to disable a bus line from search
         */
        void disableBusLineMenu();

        /**
         * Menu that allows user to disable área from a specific stop
         * or coordinate until a specific radius of meters
         */
        void disableAreaMenu();

        /**
         * Main menu that allows the user to choose between the find route menu or leave the program
         * */
        void mainMenu();

        /**
         * Menu that allows user to choose the type of route he would like to check
         */
        void routeTypeMenu();

        /**
         * Menu that allows user to choose the type of stops he would like to check
         */
        void coordTypeMenu();

        /**
         * Menu that allows user to choose the type of input he would like to check
         */
        void coordInputMenu();

        /**
         * Menu that allows user to choose search definitions
         */
        void searchDefinitionsMenu();

        /**
         * Menu that allows user to choose the type of stops he would like to search
         */
        void stopInputMenu();

        /**
         * Menu that allows user to choose how many meters can he walk
         * @return a double value containing the number of meters chosen
         */
        double footInputMenu();

    public:
        /**
         * Constructor for the menu class
         * */
        Menu();
};

#endif // PROJECT_AED_PT2_MENU_H