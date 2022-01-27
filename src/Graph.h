#ifndef PROJECT_AED_PT2_GRAPH_H
#define PROJECT_AED_PT2_GRAPH_H

#define INF (INT_MAX/2)

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <queue>
using namespace std;

/**
 * Struct that groups the two dimensions of the coordinate (latitude and longitude)
 */
struct Coordinate {

    /**
     * @var latitude, coordinates latitude, a double value
     */
    double latitude;

    /**
     * @var longitude, coordinates longitude, a double value
     */
    double longitude;
};

/**
 * Struct that groups the tree customizable weights for the Dijkstra Algorithm
 */
struct CustomWeight {

    /**
     * @var meters, a double which contains the distance between current node and origin
     */
    double meters;

    /**
     * @var numberOfLines, an integer value that contains the number of distinct lines between current node and origin
     */
    int numberOfLines;

    /**
     * @var numberOfZones, an integer value that contains the number of distinct zones between current node and origin
     */
    int numberOfZones;
};

/**
 * Struct that groups all characteristics of the edge that separates two nodes
 */
struct Edge {

    /**
     * @var dest, an integer value that represents the destination of current edge, based on node's index
     */
    int dest;

    /**
     * @var weight, a double value that represents the edge length in meters
     */
    double weight;

    /**
     * @var name, a string representing edge name
     */
    string name;
};

/**
 * Struct that represents a Stop in Porto
 */
struct Node {

    /**
     * @var code, a string that represents Stop code
     */
    string code;

    /**
     * @var name, a string that represents Stop name
     */
    string name;

    /**
     * @var zone, a string that represents Stop zone
     */
    string zone;

    /**
     * @var coordinate, a Coordinate struct type that represents Stop coordinate
     */
    Coordinate coordinate;

    /**
     * @var available, a boolean attribute that represents the current state of Stop
     */
    bool available;

    /**
     * @var adjacent, a list of Edges containing all possible paths from the current node
     */
    list<Edge> adjacent;

    /**
     * @var customWeight, a CustomWeight struct that includes all the distinct weights of current node
     */
    CustomWeight customWeight;

    /**
     * @var visited, a boolean attribute that indicates if the stop is active
     */
    bool visited;

    /**
     * @var parent, an integer value represents previous node index
     */
    int parent;

    /**
     * @var currentLine, a string representing one of the several lines the node can be on
     */
    string currentLine;

    /**
     * @var distance, an integer value containing the number of nodes between current node and origin
     */
    int distance;
};

/**
 * Class that represents a Graph and its entire structure
 */
class Graph {

    private:

        /**
         * @var nodes, a vector containing Node type struct that includes all nodes of current Graph
         */
        vector<Node> nodes;

        /**
         * Function that returns the distance between two points with coordinates passed by parameter
         * Time Complexity: O(1)
         * @param lat1 a double value represents the latitude of first point
         * @param lon1 a double value represents the longitude of first point
         * @param lat2 a double value represents the latitude of second point
         * @param lon2 a double value represents the longitude of second point
         * @return a double value containing the distance between two points
         */
        double computeDistance(double lat1, double lon1, double lat2, double lon2);

        /**
         * Function that eliminates all foot itineraries in current graph
         * Time Complexity: O(E.V), which V is the number of nodes and E is the number of edges
         */
        void deleteFootItineraries();

    public:

        /**
         * Main constructor of the class Graph
         * @param nodes integer number that represents the number of nodes that graph must have
         */
        explicit Graph(int nodes);

        /**
         * Function that clears all Nodes
         * Time Complexity: O(V), which V is the number of nodes
         */
        void clear();

        /**
         * Function that adds a new Node to the graph
         * Time Complexity: O(1)
         * @param node Node struct that contains all characteristics of the stop
         * @param index an integer value that represents the Stop index in vector
         */
        void addNode(const Node &node, int index);

        /**
         * Function that returns one Stop, based on his index
         * Time Complexity: O(1)
         * @param index an integer value that represents the Stop index in vector
         * @return Node, representing the intended stop
         */
        Node getNode(int index);

        /**
         * Function that returns one Stop, based on his coordinate
         * Time Complexity: O(V), which V is the number of Nodes
         * @param coordinate a Coordinate struct that represents the Stop coordinate
         * @return Node, representing the stop closest to the given coordinate
         */
        Node getNode(const Coordinate &coordinate);

        /**
         * Function that adds an Edge between two nodes
         * Time Complexity: O(1)
         * @param origin a integer value representing the current
         * @param destiny
         * @param name 
         */
        void addEdge(int origin, int destiny, const string &name);
        void createFootItineraries(double distance);
        void BFS(int origin);
        void dijkstraMeters(int origin);
        void dijkstraLines(int origin);
        void dijkstraZones(int origin);
        list<Node> dijkstraPath(int origin, int destination, int type);
        void disableStop(int stop);
        void disableLine(const string &line);
        void disableArea(int stop, double distance);
        void disableZone(const string &zone);
        void activateAllStops();
};

#endif //PROJECT_AED_PT2_GRAPH_H