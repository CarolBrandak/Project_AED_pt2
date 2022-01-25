#include "src/STCP.h"

int main() {

    STCP Stcp = STCP();

    Stcp.createFootItineraries(200);
    Stcp.showPath("VRZL1", "TEC", 3); // Aliados a St. Ovídeo
    cout << endl << endl;
    Stcp.showPath("VRZL1", "TEC", 1); // Aliados a St. Ovídeo

    return 0;
}