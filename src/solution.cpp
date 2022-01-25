#include <iostream>
#include <set>
using namespace std;

int main () {

    set<pair<pair<int, double>, int>> counter;

    // A = 1, B = 2 .... F = 6
    // Com os valores que estavam no esboço

    counter.insert(make_pair(make_pair(1, 0), 1));
    counter.insert(make_pair(make_pair(2, 200), 2));
    counter.insert(make_pair(make_pair(2, 120), 3));
    counter.insert(make_pair(make_pair(1, 100), 4));
    counter.insert(make_pair(make_pair(2, 130), 5));
    counter.insert(make_pair(make_pair(2, 140), 6));

    /**
     * Todos os nós saem pela ordem pretendida. A, D, C, E, F, B
     */
    while (counter.size()) {

        int u = counter.begin()->second;
        cout << static_cast<char>(u + 64) << endl;
        counter.erase(counter.begin());

    }
}