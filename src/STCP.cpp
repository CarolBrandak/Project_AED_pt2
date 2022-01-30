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

void STCP::createFootItineraries(double distance) {
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
        cout << "O ficheiro " << STOPS << " nao existe!" << endl;
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
            cout << "O ficheiro " << fileName << " nao existe!" << endl;
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
        cout << "O ficheiro " << LINES << " nao existe!" << endl;
    }
    file.close();
}

void STCP::showPath(const Coordinate &c1, const Coordinate &c2, int type) {
    showPath(graph.getNode(c1).code, graph.getNode(c2).code, type);
}

void STCP::showPath(const string &name1, const string &name2, int type) {

    auto it1 = stops.find(name1);
    auto it2 = stops.find(name2);

    if (it1 == stops.end() || it2 == stops.end()) {
        cout << "Paragem invalida!" << endl;
        return;
    }

    vector<Node> nodes = graph.makePath(stops[name1], stops[name2], type);

    if (!nodes.empty()) {

        switch (type) {
            case 1:
                cout << "Ira passar por " << nodes.size() << " paragens antes de chegar ao seu destino. Itinerario: " << endl;
                break;
            case 2:
                cout << "Ira passar por " << nodes.size() << " paragens e percorrer " << nodes.front().customWeight.meters << " metros antes de chegar ao seu destino. Itinerario: " << endl;
                break;
            case 3:
                cout << "Ira passar por " << nodes.size() << " paragens e percorrer " << nodes.front().customWeight.numberOfLines << " linhas antes de chegar ao seu destino. Itinerario: " << endl;
                break;
            case 4:
                cout << "Ira passar por " << nodes.size() << " paragens e percorrer " << nodes.front().customWeight.numberOfZones << " zonas antes de chegar ao seu destino. Itinerario: " << endl;
                break;
        }

        double lastDistance = 0;
        cout << "Paragem " << nodes[nodes.size()-1].code << " (" << nodes[nodes.size()-1].name << "), zona " << nodes[nodes.size()-1].zone << endl;
        for (size_t i = nodes.size() - 2 ; i != -1 ; i--) {
            string line = nodes[i].currentLine == "Foot" ? " metros a pe" : " metros na linha " + nodes[i].currentLine;
            cout << "Paragem " << nodes[i].code << " (" << nodes[i].name << "), zona " << nodes[i].zone << " percorrendo " <<
                nodes[i].customWeight.meters - lastDistance << line << endl;
            lastDistance = nodes[i].customWeight.meters;
        }
        cout << endl;
    }
}

void STCP::disableStop(const string &name) {
    if (stops.find(name) == stops.end()) {
        cout << "Codigo de paragem invalido" << endl;
    } else graph.disableStop(stops[name]);
}

void STCP::disableLine(const string &line) {
    if (lines.find(line) == lines.end()) {
        cout << "Codigo de linha invalido" << endl;
    } else graph.disableLine(lines[line]);
}

void STCP::disableArea(const Coordinate &coordinate, double distance) {
    disableArea(graph.getNode(coordinate).name, distance);
}

void STCP::disableArea(const string &name, double distance) {
    if (stops.find(name) == stops.end()) {
        cout << "Codigo de paragem invalido" << endl;
    } else graph.disableArea(stops[name], distance);
}

void STCP::disableZone(const string &zone) {
    graph.disableZone(zone);
}

void STCP::activateAllStops() {
    graph.activateAllStops();
}

#endif // PROJECT_AED_PT2_STCP_CPP