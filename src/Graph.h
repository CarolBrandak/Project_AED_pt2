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
    CustomWeight weight;
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
    double distance;
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
        void dijkstra(int origin);
        list<Node> dijkstraPath(int origin, int destination);
        Node getNode(int index);
        Node getNode(const Coordinate &coordinate);
        void createFootItineraries(int distance);
};

#endif //PROJECT_AED_PT2_GRAPH_H