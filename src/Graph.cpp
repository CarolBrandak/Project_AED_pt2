#ifndef PROJECT_AED_PT2_GRAPH_CPP
#define PROJECT_AED_PT2_GRAPH_CPP

#include "Graph.h"

Graph::Graph(int nodes, bool direction, bool weighty) : nodes(nodes+1) {
    this->hasDirection = direction;
    this->isWeighty = weighty;
}

void Graph::clear() {
    for (Node node : nodes) node.adjacent.clear();
    nodes.clear();
}

vector<Node> Graph::getNodes() {
    return nodes;
}

double Graph::computeDistance(int node1, int node2) {

    double lat1 = nodes[node1].coordinate.latitude , lon1 = nodes[node1].coordinate.longitude,
            lat2 = nodes[node2].coordinate.latitude, lon2 = nodes[node2].coordinate.longitude;

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}

void Graph::addNode(const Node &node) {
    this->nodes[node.index] = node;
}

void Graph::addEdge(int origin, int destiny, const string &name) {

    if (origin < 1 || destiny > nodes.size() || origin > nodes.size() || destiny < 1) return;
    double weight = isWeighty ? computeDistance(origin, destiny) : 1;
    //cout << "Origem: " << nodes[origin].coordinate.latitude << " " << nodes[origin].coordinate.longitude << endl;
    //cout << "Destino: " << nodes[destiny].coordinate.latitude << " " << nodes[destiny].coordinate.longitude << endl;
    //cout << "Distancia: " << weight << endl;
    nodes[origin].adjacent.push_back({destiny, weight, name});
    if (!hasDirection) nodes[destiny].adjacent.push_back({origin, weight, name});
}

Node Graph::getNode(int index) {
    return this->nodes[index];
}

#endif // PROJECT_AED_PT2_GRAPH_CPP