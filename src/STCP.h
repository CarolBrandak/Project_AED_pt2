#ifndef PROJECT_AED_PT2_STCP_H
#define PROJECT_AED_PT2_STCP_H

#define numberStops 2487
#define STOPS "../data/stops.csv"

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
        void createStops();
        void addStop(const Node &node);

    public:

        STCP();
        ~STCP();
        Node getStop(const string &code);

};

#endif //PROJECT_AED_PT2_STCP_H