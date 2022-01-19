#ifndef PROJECT_AED_PT2_STCP_H
#define PROJECT_AED_PT2_STCP_H

#define STOPS "data/stops.csv"

#include <iostream>
#include <string>
#include <fstream>
#include "Graph.cpp"

class STCP {

    private:

        Graph baseGraph;
        void createBaseGraph();

    public:

        STCP();
        ~STCP();

};

#endif //PROJECT_AED_PT2_STCP_H