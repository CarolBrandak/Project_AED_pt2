#include "src/STCP.h"

int main() {

    STCP Stcp = STCP();

    /**
     * Como os nós são construídos
     */
    vector<string> names = {"1AL2", "ZOID1"};
    for (const string &name : names) {
        Node stop = Stcp.getStop(name);
        cout << "Node: " << endl;
        cout << "Code: " << stop.code << endl;
        cout << "Name: " << stop.name << endl;
        cout << "Zone: " << stop.zone << endl;
        cout << "Latitude: " << stop.coordinate.latitude << endl;
        cout << "Longitude: " << stop.coordinate.longitude << endl;
        cout << "Available: " << stop.available << endl;
        cout << "Linhas a partir deste Stop:" << endl;
        for (Edge edge : stop.adjacent) {
            cout << "Edge name: " << edge.name << endl;
            cout << "Edge destity: " << edge.dest << endl;
        }

        cout << endl;
    }

    /**
     * Diferença de quilómetros / paragens entre uma pessoa que não anda nada
     * e uma pessoa que pode andar, no máximo, 200 metros entre uma paragem e outra.
     */
    cout << "Sem andar nada (só troca de linha se houver um stop com mais do que uma): " << endl;
    Stcp.showPath("1AL5", "CCC2"); // Aliados a St. Ovídeo
    cout << endl << "Pode andar, no máximo, 200 metros de uma paragem para outra (para mudar de linha, por exemplo): " << endl;
    Stcp.createFootItineraries(200);
    Stcp.showPath("1AL5", "CCC2"); // Aliados a St. Ovídeo

    return 0;
}