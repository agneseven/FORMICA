//
// Created by A on 16/10/17.
//

#ifndef QUEUE_PROVA2_MANAGE_H
#define QUEUE_PROVA2_MANAGE_H

#include "igraph.h"
#include "Coordinates.h"
#include "mobileNode.h"
#include "Grafo.h"
#include "event_list.h"


#include <vector>

//#define nvertici 13


class manage {
public:

    int nedges;
    double CurrentTime;
    event_list Lista;
    int SizeQueue;
    bool EndOfSimulation;
    int nvertici;
    std::vector<int> arrayNvertici;
    mobileNode *mobile_nodes;
    int numMob;
    Coordinates *coord_mobile_nodes;
    int nodeMob;


    std::vector<double> vec_band;      //vector containing all ifstreams pointers
    std::vector<double> vec_delays;      //vector containing all ifstreams pointers

    igraph_vector_t weights;
    //int completedTask;
    double simulationTime;
    double busyTime;
    double s;
//double tn;


    std::vector<double> serviceTime;
    std::vector<double> arrivalTime;
    std::vector<double> deletedEdges;
    bool migrationMODE;
    bool failureMODE;
    int kserverMODE;
    int nodeFail;
    int dec;
    char* modeOffloading;
    bool THRESHOLD;

    double istanteCheck;




    manage();
    ~manage();

    int initialize_graph(int argc, char** argv);

    int initialize_process(int argc, char** argv);

    void manage_mobility();

//void finish_process(igraph_t g1);

    //    Grafo* clock_process(Grafo Topology[]);
    int clock_process(int option,  int argc, char** argv);

//    Grafo* arrive(int nodeMob, int n, Grafo* Topology);
//    Grafo* generate(int nodeMob, Grafo* Topology); //(int nodeMob, igraph_real_t weights_delay);
//    Grafo* depart(int nodeMob, Grafo* Topology); //(int nodeMob, igraph_real_t weights_delay);


    void arrive(int nodeMob, int jobID, int n, int option, int argc, char** argv);
    void arrivePriority(int nodeMob, int jobID, int n, int option, int argc, char** argv);


        void generate(int nodeMob, int option,  int argc, char** argv); //(int nodeMob, igraph_real_t weights_delay);
    void depart(int nodeMob, int jobID, int option, int argc, char** argv); //(int nodeMob, igraph_real_t weights_delay);
    void failure( int option, int argc, char** argv);

    //void depart(int nodeMob);
    //void check_status(int nodeMob, igraph_real_t );

    void destroyVar();
    void statistics();
    //igraph_real_t weightsFunction(std::vector<double> vec_delays, int nedges);

    void destroyGraph();
    int randId();
    void update_node_position();
    //void check_status(int nodeMob, Grafo* Topology);
    void check_status(int nodeMob, int option, int argc, char** argv);
    void check_status_failure(int nodeMob, int option, int argc, char** argv);


    void migrate(double timeMovedtask, int from, int to, int posQueue, int nodeMob, int idTask);
    void migratePriority(double timeMovedtask, int from, int to, int posQueue, int nodeMob, int idTask);

        double delayCalculation(int i, int n);
    int randId(int nvertici);
    bool getFailureMODE();

    void kserverFailure(int currentID, int queuePosition, int nodeMob);

    double manageMigrationCost(std::vector<double> serviceTime, double transmissionCost_new, int x, double timeelab, int n, int i);
    int kserverIDgen(int currentID, int nvertici, std::vector<double> serviceTime, double timeelab);
    double migratekserverFailure(int currentID, int queuePosition, int nodeMob, double timeelab);

    double migrationCostVariableON(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab);
    double migrationCostVariableOFF(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab);
    double migrationCostUniformON(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab);
    double migrationCostUniformOFF(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab);










    };


#endif //QUEUE_PROVA2_MANAGE_H
