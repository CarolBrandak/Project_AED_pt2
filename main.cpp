#include "src/STCP.h"

int main() {

    STCP Stcp = STCP();

    vector<string> names = {"1AL2", "1BS8", "ZOID1", "ZOID2"};
    for (const string &name : names) {
        Node stop = Stcp.getStop(name);
        cout << "Node: " << endl;
        cout << "Code: " << stop.code << endl;
        cout << "Name: " << stop.name << endl;
        cout << "Zone: " << stop.zone << endl;
        cout << "Latitude: " << stop.coordinate.latitude << endl;
        cout << "Longitude: " << stop.coordinate.longitude << endl;
        cout << "Available: " << stop.available << endl;

        for (Edge edge : stop.adjacent) {
            cout << "Edge name: " << edge.name << endl;
            cout << "Edge destity: " << edge.dest << endl;
        }

        cout << endl;
    }

    return 0;
}