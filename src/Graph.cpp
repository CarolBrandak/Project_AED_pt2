#ifndef PROJECT_AED_PT2_GRAPH_CPP
#define PROJECT_AED_PT2_GRAPH_CPP

#include "Graph.h"

Graph::Graph(int nodes) : nodes(nodes+1) {
}

void Graph::clear() {
    for (Node node : nodes) node.adjacent.clear();
    nodes.clear();
}

double Graph::computeDistance(double lat1, double lon1, double lat2, double lon2) {

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}

void Graph::addNode(const Node &node, int index) {
    this->nodes[index] = node;
}

void Graph::addEdge(int origin, int destiny, const string &name) {
    if (origin < 1 || destiny > nodes.size() || origin > nodes.size() || destiny < 1) return;
    nodes[origin].adjacent.push_back({destiny, computeDistance(nodes[origin].coordinate.latitude,
                                                                   nodes[origin].coordinate.longitude,
                                                                   nodes[destiny].coordinate.latitude,
                                                                   nodes[destiny].coordinate.longitude), name});
}

void Graph::BFS(int origin) {

    for (int i = 1 ; i < nodes.size() ; i++) {
        nodes[i].visited = false;
        nodes[i].distance = 0;
        nodes[i].parent = i;
        nodes[i].currentLine = " ";
        nodes[i].customWeight.meters = 0;
    }

    if (!nodes[origin].available) {
        cout << "A origem nao esta disponivel" << endl;
        return;
    }

    queue<int> visitedNodes = {};
    visitedNodes.push(origin);
    nodes[origin].visited = true;
    nodes[origin].distance = 0;
    nodes[origin].currentLine = " ";

    while (!visitedNodes.empty()) {

        int node = visitedNodes.front();
        visitedNodes.pop();

        if (nodes[node].available) {
            for (const Edge &edge : nodes[node].adjacent) {

                int n = edge.dest;
                double w = edge.weight;

                if (!nodes[n].visited) {
                    visitedNodes.push(n);
                    nodes[n].visited = true;
                    nodes[n].distance = nodes[node].distance + 1;
                    nodes[n].parent = node;
                    nodes[n].currentLine = edge.name;
                    nodes[n].customWeight.meters = nodes[node].customWeight.meters + w;
                }
            }
        }
    }
}

void Graph::dijkstraMeters(int origin) {

    set<pair<double, int>> counter;

    for (int i = 1 ; i < nodes.size() ; i++) {
        nodes[i].customWeight.meters = INF;
        nodes[i].customWeight.numberOfLines = INF;
        nodes[i].customWeight.numberOfZones = INF;
        nodes[i].visited = false;
        nodes[i].parent = INF;
        counter.insert(make_pair(INF, i));
    }
    if (!nodes[origin].available) {
        cout << "A origem nao esta disponivel" << endl;
        return;
    }

    nodes[origin].customWeight.meters = 0;
    nodes[origin].customWeight.numberOfZones = 1;
    nodes[origin].parent = origin;
    nodes[origin].currentLine = " ";
    counter.erase({INF, origin});
    counter.insert({0, origin});

    while (!counter.empty()) {

        int u = counter.begin()->second;
        counter.erase(counter.begin());
        nodes[u].visited = true;

        for (const Edge &edge : nodes[u].adjacent) {
            int v = edge.dest;
            double w = edge.weight;
            if (!nodes[v].visited && nodes[v].available && nodes[u].customWeight.meters + w < nodes[v].customWeight.meters) {
                counter.erase({nodes[v].customWeight.meters, v});
                nodes[v].customWeight.meters = nodes[u].customWeight.meters + w;
                nodes[v].customWeight.numberOfZones = nodes[u].zone == nodes[v].zone ? nodes[u].customWeight.numberOfZones : nodes[u].customWeight.numberOfZones + 1;
                nodes[v].parent = u;
                nodes[v].currentLine = edge.name;
                counter.insert({nodes[v].customWeight.meters, v});
            }
        }
    }
}

void Graph::dijkstraLines(int origin) {

    set<pair<pair<int, double>, int>> counter;

    for(int i = 1 ; i <= nodes.size() - 1 ; i++) {
        nodes[i].customWeight.numberOfZones = INF;
        nodes[i].customWeight.meters = INF;
        nodes[i].customWeight.numberOfLines = INF;
        nodes[i].visited = false;
        nodes[i].parent = INF;
        nodes[i].currentLine = " ";
        counter.insert(make_pair(make_pair(INF, INF), i));
    }

    if (!nodes[origin].available) {
        cout << "A origem nao esta disponivel" << endl;
        return;
    }

    nodes[origin].customWeight.numberOfLines = 0;
    nodes[origin].customWeight.numberOfZones = 1;
    nodes[origin].customWeight.meters = 0;
    nodes[origin].parent = origin;
    nodes[origin].currentLine = " ";
    counter.erase({{INF, INF}, origin});
    counter.insert({{0, 0}, origin});

    while (!counter.empty()) {

        int u = counter.begin()->second;
        counter.erase(counter.begin());
        nodes[u].visited = true;

        string lastLine = nodes[u].currentLine; // verde
        string currentLine;

        for (const Edge &edge : nodes[u].adjacent) {
            int v = edge.dest;
            double w = edge.weight;
            currentLine = edge.name;
            if(!nodes[v].visited && nodes[v].available && nodes[u].customWeight.numberOfLines < nodes[v].customWeight.numberOfLines) {

                counter.erase({{nodes[v].customWeight.numberOfLines, nodes[v].customWeight.meters}, v});
                nodes[v].customWeight.meters = nodes[u].customWeight.meters + w;
                nodes[v].parent = u;

                if (lastLine == currentLine) {
                    nodes[v].customWeight.numberOfLines = nodes[u].customWeight.numberOfLines;
                    nodes[v].currentLine = lastLine;
                } else {
                    nodes[v].customWeight.numberOfLines = nodes[u].customWeight.numberOfLines + 1;
                    nodes[v].currentLine = currentLine;
                }

                nodes[v].customWeight.numberOfZones = nodes[u].zone == nodes[v].zone ?
                                                      nodes[u].customWeight.numberOfZones : nodes[u].customWeight.numberOfZones + 1;

                counter.insert(make_pair(make_pair(nodes[v].customWeight.numberOfLines, nodes[v].customWeight.meters), v));
            }
        }
    }
}

void Graph::dijkstraZones(int origin) {

    set<pair<pair<int, double>, int>> counter;

    for(int i = 1 ; i <= nodes.size() - 1 ; i++) {
        nodes[i].customWeight.numberOfZones = INF;
        nodes[i].customWeight.meters = INF;
        nodes[i].customWeight.numberOfLines = INF;
        nodes[i].visited = false;
        nodes[i].parent = INF;
        counter.insert(make_pair(make_pair(INF, INF), i));
    }

    if (!nodes[origin].available) {
        cout << "A origem nao esta disponivel" << endl;
        return;
    }

    nodes[origin].customWeight.numberOfZones = 1;
    nodes[origin].customWeight.meters = 0;
    nodes[origin].parent = origin;
    counter.erase({{INF, INF}, origin});
    counter.insert({{1, 0}, origin});

    while (!counter.empty()) {

        int u = counter.begin()->second;
        counter.erase(counter.begin());
        nodes[u].visited = true;

        for (const Edge &edge : nodes[u].adjacent) {
            int v = edge.dest;
            double w = edge.weight;
            if(!nodes[v].visited && nodes[v].available && nodes[u].customWeight.numberOfZones < nodes[v].customWeight.numberOfZones) {
                counter.erase({{nodes[v].customWeight.numberOfZones, nodes[v].customWeight.meters}, v});
                nodes[v].customWeight.meters = nodes[u].customWeight.meters + w;
                nodes[v].parent = u;
                nodes[v].currentLine = edge.name;
                nodes[v].customWeight.numberOfZones = nodes[u].zone == nodes[v].zone ?
                        nodes[u].customWeight.numberOfZones : nodes[u].customWeight.numberOfZones + 1;
                counter.insert(make_pair(make_pair(nodes[v].customWeight.numberOfZones, nodes[v].customWeight.meters), v));
            }
        }
    }
}

vector<Node> Graph::makePath(int origin, int destination, int type) {

    vector<Node> path = {};

    if (!nodes[origin].available || !nodes[destination].available) {
        cout << "Origem/Destino nao disponivel" << endl;
        return path;
    }

    switch (type) {
        case 1: BFS(origin); break;
        case 2: dijkstraMeters(origin); break;
        case 3: dijkstraLines(origin); break;
        case 4: dijkstraZones(origin); break;
    }

    if (nodes[destination].customWeight.meters == INF) return path;

    int i = destination;
    path.push_back(nodes[i]);
    while (i != origin) {
        i = nodes[i].parent;
        path.push_back(nodes[i]);
    }
    return path;
}

void Graph::deleteFootItineraries() {
    for (int i = 1; i < nodes.size(); i++) {
        nodes[i].adjacent.remove_if([](const Edge &edge) { return edge.name == "Foot"; });
    }
}

void Graph::createFootItineraries(double distance) {

    deleteFootItineraries();

    for (int i = 1 ; i < nodes.size() ; i++ ) {
        for (int j = 1 ; j < nodes.size() ; j++ ) {
            if (i != j && distance >= computeDistance(nodes[i].coordinate.latitude, nodes[i].coordinate.longitude,
                                                      nodes[j].coordinate.latitude, nodes[j].coordinate.longitude)) addEdge(i, j, "Foot");
        }
    }
}

Node Graph::getNode(const Coordinate &coordinate) {

    Node result;
    double distance = INT_MAX;
    for (int i = 1 ; i < nodes.size() ; i++) {
        double attempDistance = computeDistance(nodes[i].coordinate.latitude, nodes[i].coordinate.longitude,
                                                coordinate.latitude, coordinate.longitude);
        if (distance > attempDistance) {
            result = nodes[i];
            distance = attempDistance;
        }
    }
    return result;
}

void Graph::disableStop(int stop) {
    nodes[stop].available = false;
}

void Graph::disableLine(const string &line) {
    for (Node &node : nodes) {
        for (const Edge &edge : node.adjacent) {
            if (edge.name == line) node.available = false;
        }
    }
}

void Graph::disableArea(int stop, double distance) {

    Coordinate origin = nodes[stop].coordinate;
    for (Node &node : nodes) {
        Coordinate destiny = node.coordinate;
        if (computeDistance(origin.latitude, origin.longitude,
                            destiny.latitude, destiny.longitude) <= distance) node.available = false;
    }

}

void Graph::disableZone(const string &zone) {
    for (Node &node : nodes) {
        if (node.zone == zone) node.available = false;
    }
}

void Graph::activateAllStops() {
    for (Node &node : nodes) {
        node.available = true;
    }
}

#endif // PROJECT_AED_PT2_GRAPH_CPP