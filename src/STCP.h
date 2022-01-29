#ifndef PROJECT_AED_PT2_STCP_H
#define PROJECT_AED_PT2_STCP_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Graph.h"

/**
 * Definition of number of stops and some file paths that are useful for the class below
 */
#define numberStops 2487
#define STOPS "../data/stops.csv"
#define LINES "../data/lines.csv"

/**
 * Class to manage a public transport company and his data
 */
class STCP {

    private:

        /**
         * @var graph - a Graph class containing all data
         */
        Graph graph;

        /**
         * @var stops - a map, using string key and int value, to manage all stops
         */
        map<string, int> stops;

        /**
         * @var lines - a map, using string key and string value, to manage all lines
         */
        map<string, string> lines;

        /**
         * Function that reads and creates all stops
         * Time Complexity: O(S), which S is the number of lines in the file = number of stops to create
         */
        void createStops();

        /**
         * Function that reads and creates all lines
         * Time Complexity: O(L.S), which L is the number of lines in the file = number of Lines to create and S
         * is the number of Stops to the certain Line
         */
        void createLines();

        /**
         * Function that reads and create a line
         * Time Complexity: O(S), which S is the number of Stops in the given line
         * @param code - a string representing the code of certain line
         */
        void createLine(const string &code);

        /**
         * Function that adds a new Node to the graph
         * Time Complexity: O(1)
         * @param node - Node struct that contains all characteristics of the stop
         * @param index - an integer value that represents the Stop index in vector
         */
        void addStop(const Node &node, int index);

    public:

        /**
         * A default constructor of class
         */
        STCP();

        /**
         * A default destructor of class
         */
        ~STCP();

        /**
         * Function that creates foot itineraries, based on distance passed by value
         * Time Complexity: O(V^2), which V is the number of Nodes
         * @param distance - a double which determines maximum length of certain walk
         */
        void createFootItineraries(double distance);

        /**
         * @Overload
         * Function that prints all path based on users input
         * Time Complexity: O(V), which V is the number of Nodes
         * @param name1 - a string containing the name of certain origin stop
         * @param name2 - a string containing the name of certain destination stop
         * @param type - an integer value representing the user choice
         */
        void showPath(const string &name1, const string &name2, int type);

        /**
         * @Overload
         * Function that prints all path based on users input
         * Time Complexity: O(V), which V is the number of Nodes
         * @param c1 - a Coordinate struct containing the coordinate of certain origin stop
         * @param c2 - a Coordinate struct containing the coordinate of certain destination stop
         * @param type - an integer value representing the user choice
         */
        void showPath(const Coordinate &c1, const Coordinate &c2, int type);

        /**
         * Function that disable a Stop
         * Time Complexity: O(1)
         * @param name - a string containing the Stops name
         */
        void disableStop(const string &name);

        /**
         * Function that disables all Nodes in selected line
         * Time Complexity: O(V + E), which V is the number of Nodes and E is the number of edges
         * @param line - a string passed by reference containing the line name
         */
        void disableLine(const string &line);

        /**
        * @Overload
        * Function that disables all Nodes in selected area, based on coordinate and his radius
        * Time Complexity: O(V), which V is the number of Nodes
        * @param coordinate - a Coordinate struct containing the coordinate of selected area
        * @param distance - a double value containing the radius of the area
        */
        void disableArea(const Coordinate &coordinate, double distance);

        /**
        * @Overload
        * Function that disables all Nodes in selected area, based on name and his radius
        * Time Complexity: O(V), which V is the number of Nodes
        * @param name - a string containing the stops name
        * @param distance - a double value containing the radius of the area
        */
        void disableArea(const string &name, double distance);

        /**
        * Function that disables all nodes in selected Zone
        * Time Complexity: O(V), which V is the number of Nodes
        * @param zone - a string containing the name of selected zone
        */
        void disableZone(const string &zone);

        /**
         * Function that activates all nodes in current Graph
         * Time Complexity: O(V), which V is the number of Nodes
         */
        void activateAllStops();
};

#endif //PROJECT_AED_PT2_STCP_H