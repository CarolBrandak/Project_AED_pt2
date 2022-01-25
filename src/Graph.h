#ifndef PROJECT_AED_PT2_GRAPH_H
#define PROJECT_AED_PT2_GRAPH_H

#define INF (INT_MAX/2)

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include "MinHeap.h"
using namespace std;

struct Coordinate {
    double latitude;
    double longitude;
};

struct CustomWeight {
    double meters;
    int numberOfLines;
    int numberOfZones;
};

struct Edge {
    int dest;
    double weight;
    string name;
};

struct Node {
    string code;
    string name;
    string zone;
    Coordinate coordinate;
    bool available;
    list<Edge> adjacent;
    CustomWeight customWeight;
    bool visited;
    int parent;
    string currentLine;
};

class Graph {

    private:

        vector<Node> nodes;
        double computeDistance(double lat1, double lon1, double lat2, double lon2);

    public:

        explicit Graph(int nodes);
        void clear();
        void addNode(const Node &node, int index);
        Node getNode(int index);
        Node getNode(const Coordinate &coordinate);
        void addEdge(int origin, int destiny, const string &name);
        void createFootItineraries(int distance);
        void deleteFootItineraries();
        void dijkstraMeters(int origin);
        void dijkstraLines(int origin);
        void dijkstraZones(int origin);
        list<Node> dijkstraPath(int origin, int destination, int type);
};

#endif //PROJECT_AED_PT2_GRAPH_H