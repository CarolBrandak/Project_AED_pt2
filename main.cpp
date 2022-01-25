#include "src/STCP.h"

int main() {

    STCP Stcp = STCP();

    Stcp.createFootItineraries(200);
    Stcp.showPath("1AL5", "CCC2", 3); // Aliados a St. Ovídeo

    return 0;
}