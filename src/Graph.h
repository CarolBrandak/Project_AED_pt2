#ifndef PROJECT_AED_PT2_GRAPH_H
#define PROJECT_AED_PT2_GRAPH_H

#include <list>
#include <vector>
using namespace std;

struct Coordinate {
    float latitude;
    float longitude;
};

struct Edge {
    int dest;
    int weight;
};

struct Node {
    list<Edge> adj;
    int distance;
    Coordinate coordinate;
};

class Graph {

    private:

        int n;
        bool hasDir;
        vector<Node> nodes;

    public:

        Graph(int nodes, bool dir = false);
        void clear();

};

#endif //PROJECT_AED_PT2_GRAPH_H