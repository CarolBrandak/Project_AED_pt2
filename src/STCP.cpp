#ifndef PROJECT_AED_PT2_STCP_CPP
#define PROJECT_AED_PT2_STCP_CPP

#include "STCP.h"

STCP::STCP() : baseGraph(2487, true) {
    createBaseGraph();
}

STCP::~STCP() {
    baseGraph.clear();
}

void STCP::createBaseGraph() {

    ifstream file("data/stops.csv");
    if (file.is_open()) {
        string currentLine;
        getline(file, currentLine);

        int index = 0;
        while (!file.eof()) {

            string Code, Name, Zone, Latitude, Longitude;
            double latitude, longitude;
            Coordinate coordinate;

            getline(file, Code, ',');
            getline(file, Name, ',');
            getline(file, Zone, ',');
            getline(file, Latitude, ','); latitude = stod(Latitude);
            getline(file, Longitude); longitude = stod(Longitude);
            coordinate = {latitude, longitude};

            if (index < 10) {
                cout << "Point: " << index+1 << endl;
                cout << "Code: " << Code << endl;
                cout << "Name: " << Name << endl;
                cout << "Zone: " << Zone << endl;
                cout << "Latitude: " << coordinate.latitude << endl;
                cout << "Longitude: " << coordinate.longitude << endl;
                cout << endl;
            }
            index++;
        }

    } else {
        cout << "O ficheiro 'stops.csv' não existe!" << endl;
    }
    file.close();
}

#endif // PROJECT_AED_PT2_STCP_CPP