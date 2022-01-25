#include "src/STCP.h"

int main() {

    STCP Stcp = STCP();

    Stcp.createFootItineraries(200);
    Stcp.showPath("STN2", "PLNT1", 3);
    cout << endl << endl;
    Stcp.showPath("STN2", "PLNT1", 1);
    cout << endl << endl;
    Stcp.createFootItineraries(100);
    Stcp.showPath("STN2", "PLNT1", 2);

    return 0;
}