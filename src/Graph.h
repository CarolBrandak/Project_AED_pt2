#ifndef PROJECT_AED_PT2_GRAPH_H
#define PROJECT_AED_PT2_GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Coordinate {
    double latitude;
    double longitude;
};

struct Edge {
    int dest;
    int weight;
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

        int n;
        bool hasDirection;
        vector<Node> nodes;
        void computeDistance(const Node &node1, const Node &node2);

    public:

        Graph(int nodes, bool dir);
        void clear();
        void addNode(const Node &node);
        Node getNode(int index);
};

#endif //PROJECT_AED_PT2_GRAPH_H