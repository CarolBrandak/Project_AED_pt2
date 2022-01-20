#ifndef PROJECT_AED_PT2_STCP_CPP
#define PROJECT_AED_PT2_STCP_CPP

#include "STCP.h"

STCP::STCP() : weightyGraph(numberStops, true, true), notWeightyGraph(numberStops, true, false) {
    createStops();
    createLines();
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

vector<Node> STCP::getWeightyNodes() {
    return weightyGraph.getNodes();
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

void STCP::createLine(const string &code) {

    for (int i = 0 ; i < 2 ; i++) {

        string fileName = "../data/lines/line_" + code + "_" + to_string(i) + ".csv";
        ifstream file(fileName);
        if (file.is_open()) {

            string numberLines, lineName = lines[code];
            getline(file, numberLines);
            int numLines = stoi(numberLines);
            if (numLines) {

                string currentStop, nextStop;
                getline(file, currentStop);

                for (int j = 0 ; j < numLines - 1 ; j++ ) {
                    getline(file, nextStop);
                    weightyGraph.addEdge(stops[currentStop], stops[nextStop], lineName);
                    notWeightyGraph.addEdge(stops[currentStop], stops[nextStop], lineName);
                    currentStop = nextStop;
                }
            }

        } else {
            cout << "O ficheiro " << fileName << " não existe!" << endl;
        }
        file.close();
    }
}

void STCP::createLines() {

    ifstream file(LINES);
    if (file.is_open()) {

        string currentLine;
        getline(file, currentLine);

        while (!file.eof()) {

            string code, name;
            getline(file, code, ',');
            if (code.empty()) return;
            getline(file, name);
            lines.insert(make_pair(code, name));
            createLine(code);
        }

    } else {
        cout << "O ficheiro " << LINES << " não existe!" << endl;
    }
    file.close();
}

#endif // PROJECT_AED_PT2_STCP_CPP