#ifndef PROJECT_AED_PT2_STCP_H
#define PROJECT_AED_PT2_STCP_H

#define numberStops 2487
#define STOPS "../data/stops.csv"
#define LINES "../data/lines.csv"

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "Graph.h"

class STCP {

    private:

        Graph graph;
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
};

#endif //PROJECT_AED_PT2_STCP_H