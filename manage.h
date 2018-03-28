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


class manage {
public:
    
    int nvertici; //number of nodes in the topology
    int nedges; //number of edges in the topology
    double CurrentTime;
    event_list Lista;
    bool EndOfSimulation;
    std::vector<int> arrayNvertici; //array with the nodes still active
    mobileNode *mobile_nodes;
    int numMob; //number of mobile devices that generate packets
    Coordinates *coord_mobile_nodes; //coordinates of the mobile nodes
    int nodeMob; //id of the mobile node

    std::vector<double> vec_band;      //vector containing bandwidth of each link
    std::vector<double> vec_delays;      //vector containing dealy of each link

    igraph_vector_t weights;
    double simulationTime; //total duration of the simulation
    //double s;

    std::vector<double> serviceTime; //service time of all nodes
    std::vector<double> arrivalTime; //arrival time of all nodes
    std::vector<double> deletedEdges; //edges that are deleted because of a failure
    //migrationMode = 1 -> migration cost on: when a node overcomes the threshold, its tasks migrate only if the migration cost of the new node is better than the migration cost of the current node
    //migrationMode = 0 -> migration cost off: when a node overcomes the threshold, its tasks ALWAYS migrate
    bool migrationMODE;
    //failureMODE = 1 -> failure on: some random nodes can fail
    //failureMODE = 0 -> failure off: nodes never fail
    bool failureMODE;
    
    int nodeFail; //number of nodes thtat we want to fail
    int dec;
    // modeOffloading == uniform -> the vertex where tasks migrate is uniformly chosen among the active nodes
    // modeOffloading == variable -> the vertex where tasks migrate is chosen among the more powerful active nodes (lower service time)
    // modeOffloading == kserver -> the vertex where tasks migrate is chosen according  to kserver policy
    char* modeOffloading;
    //THRESHOLD = 0 -> tasks migrate when the threshold is overcome
    //THRESHOLD = 1 -> tasks never migrate
    bool THRESHOLD;
    //generationMode = uniform -> mobile nodes generate traffic according to a uniform distribution
    //generationMode = exponential -> mobile nodes generate traffic according to an exponential distribution
    //generationMode = HT -> mobile nodes generate traffic according to an exponential distribution (gamma)
    char* generationMode;




    manage();
    ~manage();
    //initialize graph parameters
    int initialize_graph(int argc, char** argv);

    int initialize_process(int argc, char** argv);

    void manage_mobility();
    
    int clock_process(int option,  int argc, char** argv);

    void arrive(int nodeMob, int jobID, int n, int option, int argc, char** argv);
    
    void arrivePriority(int nodeMob, int jobID, int n, int option, int argc, char** argv);

    void generate(int nodeMob, int option,  int argc, char** argv);
    
    void depart(int nodeMob, int jobID, int option, int argc, char** argv);
    
    void failure( int option, int argc, char** argv);
    
    void statistics();

    void destroyGraph();
    
    int randId(int nvertici);

    void update_node_position();

    void check_status(int nodeMob, int option, int argc, char** argv);
    
    void check_status_failure(int nodeMob, int option, int argc, char** argv);

    void migrate(double timeMovedtask, int from, int to, int posQueue, int nodeMob, int idTask);
    
    void migratePriority(double timeMovedtask, int from, int to, int posQueue, int nodeMob, int idTask);

    double delayCalculation(int i, int n);
    
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
