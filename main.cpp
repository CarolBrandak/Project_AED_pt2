#include "src/STCP.h"

int main() {

    STCP Stcp = STCP();

    vector<string> names = {"1AL2", "1BS8", "ZOID1", "ZOID2"};
    for (string name : names) {
        Node node = Stcp.getStop(name);
        cout << "Node: " << endl;
        cout << "Code: " << node.code << endl;
        cout << "Name: " << node.name << endl;
        cout << "Zone: " << node.zone << endl;
        cout << "Latitude: " << node.coordinate.latitude << endl;
        cout << "Longitude: " << node.coordinate.longitude << endl;
        cout << endl;
    }

    return 0;
}