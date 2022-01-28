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
         * @var 
         */
        map<string, int> stops;
        map<string, string> lines;
        void createStops();
        void createLines();
        void createLine(const string &code);
        void addStop(const Node &node, int index);

    public:

        STCP();
        ~STCP();
        Node getStop(const string &code);
        void createFootItineraries(double distance);
        void showPath(const string &name1, const string &name2, int type);
        void showPath(const Coordinate &c1, const Coordinate &c2, int type);
        void showPath(const string &name1, const Coordinate &c2, int type);
        void showPath(const Coordinate &c1, const string &name2, int type);
        void disableStop(const string &name);
        void disableLine(const string &line);
        void disableArea(const Coordinate &coordinate, double distance);
        void disableArea(const string &name, double distance);
        void disableZone(const string &zone);
        void activateAllStops();
};

#endif //PROJECT_AED_PT2_STCP_H