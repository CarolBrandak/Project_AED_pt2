#ifndef PROJECT_AED_PT2_STCP_H
#define PROJECT_AED_PT2_STCP_H

// Uma classe de dados. Contém todos os grafos, leitores, e métodos de search / comparação
// O menu tem acesso aos métodos e para cada case: STCP.getDistance("FEUP", "FEP") ou por coordenadas ou por aí vai

#include <iostream>
#include <string>
#include <fstream>
#include "Graph.h"

class STCP {

    private:

        Graph baseGraph;
        void createBaseGraph();

    public:

        STCP();
        ~STCP();

};

#endif //PROJECT_AED_PT2_STCP_H