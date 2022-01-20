#ifndef PROJECT_AED_PT2_GRAPH_CPP
#define PROJECT_AED_PT2_GRAPH_CPP

#include "Graph.h"

Graph::Graph(int nodes, bool dir) : nodes(nodes+1) {
    this->hasDirection = dir;
}

void Graph::clear() {
    for (Node node : nodes) node.adjacent.clear();
    nodes.clear();
}

void Graph::addNode(const Node &node) {
    this->nodes[node.index] = node;
}

Node Graph::getNode(int index) {
    return this->nodes[index];
}

#endif // PROJECT_AED_PT2_GRAPH_CPP