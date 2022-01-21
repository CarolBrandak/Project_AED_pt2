#ifndef PROJECT_AED_PT2_GRAPH_H
#define PROJECT_AED_PT2_GRAPH_H

#define INF (INT_MAX/2)

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "MinHeap.h"
using namespace std;

struct Coordinate {
    double latitude;
    double longitude;
};

struct CustomWeight {
    double meters;
    int numberOfStops;
    int numberOfZones;
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
    CustomWeight customWeight;
    bool visited;
    int parent;
};

class Graph {

    private:

        vector<Node> nodes;
        double computeDistance(int node1, int node2);

    public:

        explicit Graph(int nodes);
        void clear();
        void addNode(const Node &node);
        void addEdge(int origin, int destiny, const string &name);
        void dijkstraMeters(int origin);
        list<Node> dijkstraPath(int origin, int destination);
        Node getNode(int index);
        void createFootItineraries(int distance);
};

#endif //PROJECT_AED_PT2_GRAPH_H