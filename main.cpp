#include <iostream>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "igraph.h"
#ifdef __cplusplus
}
#endif
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <cmath>
#include "Grafo.h"
#include "Coordinates.h"
#include "RandomWalk.h"
#include "manage.h"
#include "event_list.h"
#include "mobileNode.h"



#define PI (3.141592653589793)


Grafo* Topology;


int main(int argc, char** argv) {


    if (argc != 19) {
        std::cout << "Error: wrong number of parameters" << std::endl;
        exit(1);
    }
    int nvertici = atoi(argv[1]); //total number of vertices
    Topology = new Grafo[nvertici];


    manage(m);

    m.initialize_graph(argc, argv);

    int option = m.initialize_process(argc, argv);
    bool EndOfSimulation;
    int completedTask = 0;
    do{
        completedTask = m.clock_process(option, argc, argv);
    }while(completedTask < 500);
    //while(EndOfSimulation == false);

    m.statistics();
    m.destroyGraph();

    return 0;
}