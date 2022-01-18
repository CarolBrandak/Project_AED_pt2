#ifndef PROJECT_AED_PT2_STCP_CPP
#define PROJECT_AED_PT2_STCP_CPP

#include "STCP.h"

STCP::STCP() {
    this->baseGraph = Graph(2487, true);
    createBaseGraph(); // vai ler o ficheiro e criar os nós
}

STCP::~STCP() {
    // dar clear quando tivermos algo
    babaseGraph.clear();
}

void STCP::createBaseGraph() {

    ifstream file("../data/stops.csv");
    if (file.is_open()) {
        string currentLine;
        getline(file, currentLine);
        while (!file.eof()) {

            string 2487;

        }

    } else {
        cout << "Não existe este ficheiro!" << endl;
    }
    file.close();
}

#endif // PROJECT_AED_PT2_STCP_CPP