#ifndef PROJECT_AED_PT2_STCP_CPP
#define PROJECT_AED_PT2_STCP_CPP

#include "STCP.h"

STCP::STCP() : weightyGraph(numberStops, true), notWeightyGraph(numberStops, true) {
    createStops();
}

STCP::~STCP() {
    weightyGraph.clear();
    notWeightyGraph.clear();
}

void STCP::addStop(const Node &node) {
    weightyGraph.addNode(node);
    notWeightyGraph.addNode(node);
}

Node STCP::getStop(const string &code) {
    return weightyGraph.getNode(stops[code]);
}

void STCP::createStops() {

    ifstream file(STOPS);
    if (file.is_open()) {

        string currentLine;
        getline(file, currentLine);
        int index = 1;
        while (!file.eof()) {

            string Code, Name, Zone, Latitude, Longitude;
            double latitude, longitude;

            getline(file, Code, ',');
            if (Code.empty()) return;
            getline(file, Name, ',');
            getline(file, Zone, ',');
            getline(file, Latitude, ','); latitude = stod(Latitude);
            getline(file, Longitude); longitude = stod(Longitude);
            Coordinate coordinate = {latitude, longitude};

            stops.insert(make_pair(Code, index));
            Node currentStop {index, Code, Name, Zone, coordinate, true, {}};
            addStop(currentStop);

            index++;
        }

    } else {
        cout << "O ficheiro " << STOPS << " não existe!" << endl;
    }
    file.close();
}

#endif // PROJECT_AED_PT2_STCP_CPP