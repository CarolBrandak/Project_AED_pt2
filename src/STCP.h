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

        Graph weightyGraph;
        Graph notWeightyGraph;
        map<string, int> stops;
        map<string, string> lines;
        void createStops();
        void createLines();
        void createLine(const string &code);
        void addStop(const Node &node);

    public:

        STCP();
        ~STCP();
        Node getStop(const string &code);
        Node getStop(const Coordinate &coordinate);
};

#endif //PROJECT_AED_PT2_STCP_H