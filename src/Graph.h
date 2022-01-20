#ifndef PROJECT_AED_PT2_GRAPH_H
#define PROJECT_AED_PT2_GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

struct Coordinate {
    double latitude;
    double longitude;
};

struct Edge {
    int dest;
    double weight;
    string name;
};

struct Node {
    int index;
    string code;
    string name;
    string zone;
    Coordinate coordinate;
    bool available;
    list<Edge> adjacent;
};

class Graph {

    private:

        bool hasDirection;
        bool isWeighty;
        vector<Node> nodes;
        double computeDistance(int node1, int node2);

    public:

        Graph(int nodes, bool direction, bool weighty);
        void clear();
        void addNode(const Node &node);
        void addEdge(int origin, int destiny, const string &name);
        Node getNode(int index);
        vector<Node> getNodes();
};

#endif //PROJECT_AED_PT2_GRAPH_H