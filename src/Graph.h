#ifndef PROJECT_AED_PT2_GRAPH_H
#define PROJECT_AED_PT2_GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <queue>
using namespace std;

/**
 * Definition of the largest number used in class bellow
 */
#define INF (INT_MAX/2)

/**
 * Struct that groups the two dimensions of the coordinate (latitude and longitude)
 */
struct Coordinate {

    /**
     * @var latitude - coordinates latitude, a double value
     */
    double latitude;

    /**
     * @var longitude - coordinates longitude, a double value
     */
    double longitude;
};

/**
 * Struct that groups the tree customizable weights for the Dijkstra Algorithm
 */
struct CustomWeight {

    /**
     * @var meters - a double which contains the distance between current node and origin
     */
    double meters;

    /**
     * @var numberOfLines - an integer value that contains the number of distinct lines between current node and origin
     */
    int numberOfLines;

    /**
     * @var numberOfZones - an integer value that contains the number of distinct zones between current node and origin
     */
    int numberOfZones;
};

/**
 * Struct that groups all characteristics of the edge that separates two nodes
 */
struct Edge {

    /**
     * @var dest - an integer value that represents the destination of current edge, based on node's index
     */
    int dest;

    /**
     * @var weight - a double value that represents the edge length in meters
     */
    double weight;

    /**
     * @var name - a string representing edge name
     */
    string name;
};

/**
 * Struct that represents a Stop in Porto
 */
struct Node {

    /**
     * @var code - a string that represents Stop code
     */
    string code;

    /**
     * @var name - a string that represents Stop name
     */
    string name;

    /**
     * @var zone - a string that represents Stop zone
     */
    string zone;

    /**
     * @var coordinate - a Coordinate struct type that represents Stop coordinate
     */
    Coordinate coordinate;

    /**
     * @var available - a boolean attribute that represents the current state of Stop
     */
    bool available;

    /**
     * @var adjacent - a list of Edges containing all possible paths from the current node
     */
    list<Edge> adjacent;

    /**
     * @var customWeight - a CustomWeight struct that includes all the distinct weights of current node
     */
    CustomWeight customWeight;

    /**
     * @var visited - a boolean attribute that indicates if the stop is active
     */
    bool visited;

    /**
     * @var parent - an integer value represents previous node index
     */
    int parent;

    /**
     * @var currentLine - a string representing one of the several lines the node can be on
     */
    string currentLine;

    /**
     * @var distance - an integer value containing the number of nodes between current node and origin
     */
    int distance;
};

/**
 * Class that represents a Graph and its entire structure
 */
class Graph {

    private:

        /**
         * @var nodes - a vector containing Node type struct that includes all nodes of current Graph
         */
        vector<Node> nodes;

        /**
         * Function that returns the distance between two points with coordinates passed by parameter
         * Time Complexity: O(1)
         * @param lat1 - a double value represents the latitude of first point
         * @param lon1 - a double value represents the longitude of first point
         * @param lat2 - a double value represents the latitude of second point
         * @param lon2 - a double value represents the longitude of second point
         * @return a double value containing the distance between two points
         */
        double computeDistance(double lat1, double lon1, double lat2, double lon2);

        /**
         * Function that eliminates all foot itineraries in current graph
         * Time Complexity: O(E + V), which V is the number of nodes and E is the number of edges
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
         * @param node - Node struct that contains all characteristics of the stop
         * @param index - an integer value that represents the Stop index in vector
         */
        void addNode(const Node &node, int index);

        /**
         * @Overload
         * Function that returns one Stop, based on his coordinate
         * Time Complexity: O(V), which V is the number of Nodes
         * @param coordinate - a Coordinate struct that represents the Stop coordinate
         * @return a Node struct, representing the stop closest to the given coordinate
         */
        Node getNode(const Coordinate &coordinate);

        /**
         * Function that adds an Edge between two nodes
         * Time Complexity: O(1)
         * @param origin - a integer value representing the index of origin Node
         * @param destiny - a integer value representing the index of destiny Node
         * @param name - a string containing the lines name
         */
        void addEdge(int origin, int destiny, const string &name);

        /**
         * Function that adds more Edges between nodes, based on theirs distance
         * Time Complexity: O(V^2), which V is the number of Nodes
         * @param distance - a double value containing the maximum distance that new Edge may have
         */
        void createFootItineraries(double distance);

        /**
         * Breadth-first search to determinate the distance, in nodes, between two stops
         * Time Complexity: O(V + E), which V is the number of Nodes and E is the number of edges
         * @param origin - index of origin stop
         */
        void BFS(int origin);

        /**
         * Dijkstra Algorithm, based on distance between nodes
         * Time Complexity: O(V + V.log(V) + E.log(V)) -> O(E.log(V)), which V is the number of Nodes and
         * E is the number of edges
         * @param origin - index of origin stop
         */
        void dijkstraMeters(int origin);

        /**
         * Dijkstra Algorithm, based on number of distinct lines
         * Time Complexity: O(V + V.log(V) + E.log(V)) -> O(E.log(V)), which V is the number of Nodes and
         * E is the number of edges
         * @param origin - index of origin stop
         */
        void dijkstraLines(int origin);

        /**
         * Dijkstra Algorithm, based on number of distinct zones
         * Time Complexity: O(V + V.log(V) + E.log(V)) -> O(E.log(V)), which V is the number of Nodes and
         * E is the number of edges
         * @param origin - index of origin stop
         */
        void dijkstraZones(int origin);

        /**
         * Function that returns a path based on users input
         * Time Complexity: O(V), which V is the number of Nodes
         * @param origin - index of origin stop
         * @param destination - index of destination stop
         * @param type - an integer value containing the searching type, based on users input
         * @return a vector of Node structs that containing all path between origin and destination nodes
         */
        vector<Node> makePath(int origin, int destination, int type);

        /**
         * Function that disable a Stop
         * Time Complexity: O(1)
         * @param stop - an integer value containing the index of Stop
         */
        void disableStop(int stop);

        /**
         * Function that disables all Nodes in selected line
         * Time Complexity: O(V + E), which V is the number of Nodes and E is the number of edges
         * @param line - a string passed by reference containing the line name
         */
        void disableLine(const string &line);

        /**
         * Function that disables all Nodes in selected area, based on stop and his radius
         * Time Complexity: O(V), which V is the number of Nodes
         * @param stop - an integer value containing the index of selected stop
         * @param distance - a double value containing the radius of the area
         */
        void disableArea(int stop, double distance);

        /**
         * Function that disables all nodes in selected Zone
         * Time Complexity: O(V), which V is the number of Nodes
         * @param zone - a string containing the name of selected zone
         */
        void disableZone(const string &zone);

        /**
         * Function that activates all nodes in current Graph
         * Time Complexity: O(V), which V is the number of Nodes
         */
        void activateAllStops();
};

#endif //PROJECT_AED_PT2_GRAPH_H