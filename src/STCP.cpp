#ifndef PROJECT_AED_PT2_STCP_CPP
#define PROJECT_AED_PT2_STCP_CPP

#include "STCP.h"

STCP::STCP() : graph(numberStops) {
    createStops();
    createLines();
}

STCP::~STCP() {
    graph.clear();
}

void STCP::addStop(const Node &node, int index) {
    graph.addNode(node, index);
}

Node STCP::getStop(const string &code) {
    return graph.getNode(stops[code]);
}

void STCP::createFootItineraries(int distance) {
    graph.createFootItineraries(distance);
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
            Node currentStop {Code, Name, Zone, coordinate, true, {}};
            addStop(currentStop, index);

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
                    graph.addEdge(stops[currentStop], stops[nextStop], lineName);
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

void STCP::showPath(const Coordinate &c1, const Coordinate &c2, int type) {
    showPath(graph.getNode(c1).name, graph.getNode(c2).name, type);
}

void STCP::showPath(const string &name1, const Coordinate &c2, int type) {
    showPath(name1, graph.getNode(c2).name, type);
}

void STCP::showPath(const Coordinate &c1, const string &name2, int type) {
    showPath(graph.getNode(c1).name, name2, type);
}

void STCP::showPath(const string &name1, const string &name2, int type) {


    list<Node> nodes = graph.dijkstraPath(stops[name1], stops[name2], type);

    for (const Node &node : nodes) {
        cout << "Code: " << node.code << ", zone: " << node.zone <<
        " and coordinates: " << node.coordinate.latitude << " " << node.coordinate.longitude << endl;
    }

    cout << "Distancia total percorrida: " << graph.getNode(stops[name2]).customWeight.meters << " metros, "
    << graph.getNode(stops[name2]).customWeight.numberOfZones << " zonas e " << graph.getNode(stops[name2]).customWeight.numberOfLines << " lines." << endl;
}

#endif // PROJECT_AED_PT2_STCP_CPP