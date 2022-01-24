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

Node Graph::getNode(int index) {
    return this->nodes[index];
}

void Graph::dijkstraMeters(int origin) {

    MinHeap<int, double> counter = MinHeap<int, double>(nodes.size(), -1);

    for (int i = 1 ; i <= nodes.size() - 1 ; i++) {
        nodes[i].customWeight.meters = INF;
        nodes[i].customWeight.numberOfLines = INF;
        nodes[i].customWeight.numberOfZones = INF;
        nodes[i].visited = false;
        nodes[i].parent = INF;
        counter.insert(i, INF);
    }

    nodes[origin].customWeight.meters = 0;
    counter.decreaseKey(origin, 0);

    while (counter.getSize()) {

        int u = counter.removeMin();
        nodes[u].visited = true;
        for (const Edge &edge : nodes[u].adjacent) {
            int v = edge.dest;
            double w = edge.weight;
            if (!nodes[v].visited && nodes[u].customWeight.meters + w < nodes[v].customWeight.meters) {
                nodes[v].customWeight.meters = nodes[u].customWeight.meters + w;
                counter.decreaseKey(v, nodes[v].customWeight.meters);
                nodes[v].parent = u;
            }
        }
    }
}

void Graph::dijkstraLines(int origin) {

    MinHeap<int, int> counter = MinHeap<int, int>(nodes.size(), -1);

    for (int i = 1; i <= nodes.size() - 1; i++) {
        nodes[i].customWeight.meters = INF;
        nodes[i].customWeight.numberOfLines = INF;
        nodes[i].customWeight.numberOfZones = INF;
        nodes[i].visited = false;
        nodes[i].parent = INF;
        counter.insert(i, INF);
    }

    nodes[origin].customWeight.numberOfLines = 1;
    nodes[origin].customWeight.meters = 0;
    counter.decreaseKey(origin, 1);

    string currentLine = " ";
    bool foundSameLine;

    while (counter.getSize()) {

        int u = counter.removeMin();
        nodes[u].visited = true;
        foundSameLine = false;

        // Se encontrar uma edge que leva a uma linha semelhante, então encontra a linha
        // com menor distância e puxa

        for (const Edge &edge: nodes[u].adjacent) {
            int v = edge.dest;
            double w = edge.weight;
            string lineName = edge.name;
            if (lineName == currentLine && !nodes[v].visited) {
                cout << "Aqui dentro da linha " << edge.name << endl;
                foundSameLine = true;
                nodes[v].customWeight.meters = nodes[u].customWeight.meters + w;
                counter.decreaseKey(v, nodes[v].customWeight.numberOfLines);
                nodes[v].parent = u;
            }
        }
        // Se não encontrar uma linha semelhante, então adopta a linha de menor distância
        // Fica igual ao "Meters", mas adiciona-se ao contador e atualiza-se a currentLine

        if (!foundSameLine) {

            for (const Edge &edge: nodes[u].adjacent) {
                int v = edge.dest;
                double w = edge.weight;
                if (!nodes[v].visited && nodes[u].customWeight.meters + w < nodes[v].customWeight.meters) {
                    cout << "Verifica edge: " << edge.name << endl;
                    nodes[v].customWeight.meters = nodes[u].customWeight.meters + w;
                    cout << "Metros do v: " << nodes[v].customWeight.meters << endl;
                    counter.decreaseKey(v, nodes[u].customWeight.numberOfLines+1);
                    nodes[v].parent = u;
                    currentLine = edge.name;
                }
            }
        }
    }
}

void Graph::dijkstraZones(int origin) {

    MinHeap<int,int> counter = MinHeap<int,int>(nodes.size(),-1);
    for(int i = 1; i <= nodes.size(); i++) {
        nodes[i].customWeight.numberOfZones = INF;
        nodes[i].customWeight.meters = INF;
        nodes[i].customWeight.numberOfLines = INF;
        nodes[i].visited = false;
        nodes[i].parent = INF;
        counter.insert(i,INF);
    }

    nodes[origin].customWeight.numberOfZones = 1;
    counter.decreaseKey(origin,1);

    while(counter.getSize()) {
        bool foundSameZone= false;
        int u = counter.removeMin();
        nodes[u].visited = true;
        for(const Edge &edge : nodes[u].adjacent) {
            int destinyNode = edge.dest;
            string destinyNodeZone = nodes[destinyNode].zone;
            if(!nodes[destinyNode].visited && nodes[u].zone == nodes[destinyNode].zone) {
                nodes[destinyNode].customWeight.numberOfZones = nodes[u].customWeight.numberOfZones;
                nodes[destinyNode].customWeight.meters = nodes[u].customWeight.meters + edge.weight;
                counter.decreaseKey(destinyNode,nodes[destinyNode].customWeight.numberOfZones);
                nodes[destinyNode].parent=u;
                foundSameZone= true;
            }
        }
        if (!foundSameZone){
            for(const Edge &edge : nodes[u].adjacent) {
                int destinyNode = edge.dest;
                string destinyNodeZone = nodes[destinyNode].zone;
                if(!nodes[destinyNode].visited && nodes[u].customWeight.meters + edge.weight < nodes[destinyNode].customWeight.meters) {
                    nodes[destinyNode].customWeight.meters = nodes[u].customWeight.meters + edge.weight;
                    nodes[destinyNode].customWeight.numberOfZones = nodes[u].customWeight.numberOfZones +1;
                    counter.decreaseKey(destinyNode, nodes[destinyNode].customWeight.numberOfZones);
                    nodes[destinyNode].parent = u;

                }
            }
        }
    }
}

list<Node> Graph::dijkstraPath(int origin, int destination, int type) {

    switch (type) {
        case 1: dijkstraMeters(origin); break;
        case 2: dijkstraLines(origin); break;
        case 3: dijkstraZones(origin); break;
    }

    list<Node> path = {};
    if (nodes[destination].customWeight.meters == INF) return path;

    int i = destination;
    path.push_back(nodes[i]);
    while (i != origin) {
        i = nodes[i].parent;
        path.push_front(nodes[i]);
    }
    return path;
}

void Graph::deleteFootItineraries() {
    for (int i = 1; i < nodes.size(); i++) {
        nodes[i].adjacent.remove_if([](const Edge &edge) { return edge.name == "Foot"; });
    }
}

void Graph::createFootItineraries(int distance) {

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
        if (distance < attempDistance) {
            result = nodes[i];
            distance = attempDistance;
        }
    }
    return result;
}

#endif // PROJECT_AED_PT2_GRAPH_CPP