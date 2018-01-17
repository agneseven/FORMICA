//
// Created by A on 16/10/17.
//

#include "manage.h"

#include "event_list.h"
#include "Grafo.h"
#include "Coordinates.h"
#include "RandomWalk.h"
#include "mobileNode.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iterator>
#include "igraph.h"
#include <algorithm>


#define PI (3.141592653589793)
#define ELABORATION_TIME 0 //s
#define SPEED_OF_LIGHT  299792458.0 // m/s


extern Grafo* Topology;
igraph_t g1;
std::vector<double> totLifeTaskTime;
std::vector<int> jobIDLifeTaskTime;
int totGeneratedEvent;
int totcompletedTask;
int migration;
int NOmigration;
int NOconnection;
int lostTask;
int failedVertex;
//int Freq_n[10];
int sogliasuperata;
std::vector<int> vecThreshold;
std::default_random_engine generator;






double Coord_rand(double Border){
    double range = (Border - 0);
    double div = RAND_MAX / range;
    return 0 + (rand() / div);
}


int manage::randId(int nvertici){
    // std::cout << "rand " << std::endl;
    double range = (nvertici - 0);
    double div = RAND_MAX / range;
    return 0 + (rand() / div);

}


int preferentialIDgen(int i, int nvertici, std::vector<double> serviceTime){
    std::vector<double> listProb;
    double sumlistMigrationCost = 0;
    int n;


    for (int id = 0; id < nvertici; id++) {
        if (Topology[id].getState() == 1 && id != i && Topology[i].getNeighbours(id) == 1) {
            //std::cout << "id ok " << id << std::endl;
            sumlistMigrationCost = sumlistMigrationCost + (1 / serviceTime[id]);
        }
    }

    for (int id = 0; id < nvertici; id++) {
        if (Topology[id].getState() == 1 && id != i && Topology[i].getNeighbours(id) == 1) {
            listProb.push_back((1 / serviceTime[id]) / sumlistMigrationCost);
            // std::cout << "probailita node " << id << ": " << listProb[id]<< std::endl;
        } else if (Topology[id].getState() == 0 || id == i || Topology[i].getNeighbours(id) == 0) {
            listProb.push_back(0);
            //std::cout << "probailita node " << id << ": " << listProb[id]<< std::endl;
        }
    }

    double val = (double) rand() / RAND_MAX;
    double cumulativeProbability = 0;
    //                            std::cout << "val " << val <<  std::endl;

    for (int id = 0; id < nvertici; id++) {
        if (Topology[id].getState() == 1 && Topology[i].getNeighbours(id) == 1) {
            //std::cout << "id " << id <<  std::endl;

            cumulativeProbability = cumulativeProbability + listProb[id];
            //std::cout << "cumulativeProbability " << cumulativeProbability << " val " << val <<  std::endl;

            if (val < cumulativeProbability && id != i) {
                n = id;
                //std::cout << "nodo ud " << id <<  std::endl;
                break;
            }
        }
    }

    return n;

}

int powerfulIDgen(int nvertici, std::vector<double> serviceTime){
    std::vector<double> listProb;
    double sumlistMigrationCost = 0;

    for (int id = 0; id < nvertici; id++) {
        if(Topology[id].getState() == 1 )
            sumlistMigrationCost = sumlistMigrationCost + (1/serviceTime[id]);
    }

    for (int id = 0; id < nvertici; id++) {
        if(Topology[id].getState() == 1){
            listProb.push_back((1/serviceTime[id])/sumlistMigrationCost);
            // std::cout << "probailita node " << i << ": " << listProb[i]<< std::endl;
        }
        else if(Topology[id].getState() == 0){
            listProb.push_back(0);
        }
    }

    int n;
    double val = (double)rand() / RAND_MAX;
    double cumulativeProbability = 0;
    //                            std::cout << "val " << val <<  std::endl;

    for (int id = 0; id < nvertici; id++) {
        if(Topology[id].getState() == 1 ){
            //std::cout << "id " << id <<  std::endl;

            cumulativeProbability =  cumulativeProbability + listProb[id];
            //std::cout << "cumulativeProbability " << cumulativeProbability << " val " << val <<  std::endl;

            if (val < cumulativeProbability) {
                n = id;
                //std::cout << "nodo ud " << id <<  std::endl;

                break;
            }
        }
    }
    return n;

}

int manage::kserverIDgen(int currentID, int nvertici, std::vector<double> serviceTime, double timeelab){
    std::vector<double> listMigrationCost;
    double sumlistMigrationCost = 0;

    for (int id = 0; id < nvertici; id++) {
        if (Topology[id].getState() == 1 && id != currentID && Topology[currentID].getNeighbours(id) == 1) {
            double transmissionCost_new = delayCalculation(currentID, id);
            double queueCost_new = serviceTime[id] * (Topology[id].getSizeQueue());
            //std::cout << "Topology[id].getSizeQueue()-1 " << Topology[id].getSizeQueue()<< std::endl;
            //double lastTaskCost_new = serviceTime[n] - CurrentTime;
            double elaborationTime_new = timeelab;
            listMigrationCost.push_back(transmissionCost_new + queueCost_new  + elaborationTime_new);
            // std::cout << "MigrationCost " << id << ": " <<  listMigrationCost[id]<< std::endl;

            sumlistMigrationCost = sumlistMigrationCost + (1/listMigrationCost[id]);
        }
        else if (Topology[id].getState() == 0 || id == currentID || Topology[currentID].getNeighbours(id) == 0) {
            listMigrationCost.push_back(0);
        }
    }

    std::vector<double> listProb;


    for (int id = 0; id < nvertici; id++) {
        if (Topology[id].getState() == 1 && id != currentID && Topology[currentID].getNeighbours(id) == 1) {
            listProb.push_back((1/listMigrationCost[id])/sumlistMigrationCost);
            // std::cout << "probailita node " << id << ": " << listProb[id]<< std::endl;
        }
        else if (Topology[id].getState() == 0 || id == currentID || Topology[currentID].getNeighbours(id) == 0) {
            listProb.push_back(0);
        }
    }


    double val = (double)rand() / RAND_MAX;
    double cumulativeProbability = 0;
    //std::cout << "val " << val <<  std::endl;

    int n;



    for (int id = 0; id < nvertici; id++) {
        if (Topology[id].getState() == 1 && Topology[currentID].getNeighbours(id) == 1) {
            cumulativeProbability = cumulativeProbability + listProb[id];
            //std::cout << "cumulativeProbability " << cumulativeProbability << " val " << val <<  std::endl;
            if (val < cumulativeProbability && id != currentID) {
                n = id;
                //std::cout << "nodo ud " << id <<  std::endl;
                break;
            }
        }
    }

    return n;
}






//================================================== =======================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers =
//= - x_n = 7^5*x_(n-1)mod(2^31 - 1) =
//= - With x seeded to 1 the 10000th x value should be 1043618065 =
//= - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//= John Wiley & Sons, 1991. (Page 443, Figure 26.2) =
//= - Seed the RNG if seed > 0, return a unif(0,1) if seed == 0 =
//================================================== =======================


//================================================== ============================
//= Function to generate exponentially distributed RVs using inverse method =
//= - Input: x (mean value of distribution) =
//= - Output: Returns with exponential RV =
//================================================== ============================
double exponential(double x)
{
    double z; // Uniform random number from 0 to 1


    // Pull a uniform RV (0 < z < 1)
    do
    {
        z = ((double) rand() / RAND_MAX);
    }
    while ((z == 0) || (z == 1));

    return(-x * log(z));
}



manage::manage(){//(int idn) {//, double x, double y){

}


manage::~manage(){
}




int manage::initialize_process(int argc, char** argv) {
    //tn = 0;
    //s = 0;
    totGeneratedEvent = 0;
    failedVertex = 0;
//    for (int a=0; a < nvertici; a++){
//        Freq_n[a] = 0;
//    }

    migration = 0;
    lostTask = 0;

    NOmigration = 0;
    NOconnection = 0;

    simulationTime = atof(argv[6]); //1000;
    busyTime = 0;
    totcompletedTask = 0;
    EndOfSimulation = false;
    Event *ev;

    sogliasuperata = 0;

    istanteCheck = 0.0;


    numMob = atoi(argv[7]);
    coord_mobile_nodes = new Coordinates;

    mobile_nodes = new mobileNode[numMob];
    double tGen = 0;
    for(int i = 0; i < numMob; i++){
        //std::cout << "nodo mobile " <<  i << " genera un task " << std::endl;
        tGen =  (double)(rand()%2) + (double)rand() / (double)RAND_MAX;

        //std::cout << "tGen " <<  tGen <<  std::endl;
        ev = new Event(GENERATION, tGen, i, 0, 0); // at the instant 0 a new event arrival happensù
        Lista.addEvent(ev); //add to the list of event this one

        //totGeneratedEvent++;

    }

    //---------------------------------------------------------
    char* modeTs;
    char* modeTd;

    modeTs = argv[8];
    modeTd = argv[9];

    const std::string uniformMode = "uniform";
    const std::string exponentialMode = "exponential";
    const std::string constantMode = "constant";
    int option;
    if(modeTs == uniformMode && modeTd == uniformMode){
        option = 0;
    }
    else if(modeTs == exponentialMode && modeTd == exponentialMode){
        option = 1;
    }
    else if(modeTs == constantMode && modeTd == constantMode){
        option = 2;
    }
    else if(modeTs == constantMode && modeTd == uniformMode){
        option = 3;
    }
    else if(modeTs == uniformMode && modeTd == constantMode){
        option = 4;
    }

    std::default_random_engine generator;

    switch(option) {
        case (0): {
            double maxUnifValueTS = atof(argv[10]);
            std::uniform_real_distribution<> distributionUnifTS(0, maxUnifValueTS);
            double maxUnifValueTD = atof(argv[11]);
            std::uniform_real_distribution<> distributionUnifTD(0, maxUnifValueTD);

            for (int i = 0; i < nvertici; i++) {
                double TSvalue = 0;
                while (TSvalue == 0) {
                    TSvalue = distributionUnifTS(generator);
                }
                serviceTime.push_back(TSvalue);
                std::cout << " mean service time " << serviceTime[i] << std::endl;
            }

            for (int i = 0; i < nvertici; i++) {
                double TDvalue = 0;
                while (TDvalue == 0) {
                    TDvalue = distributionUnifTD(generator);
                }
                arrivalTime.push_back(TDvalue);
                std::cout << " mean generation time " << arrivalTime[i] << std::endl;
            }

            break;
        }

        case (1): {
            double avgExpValueTS = atof(argv[10]);
            std::exponential_distribution<double> distributionExpTS(avgExpValueTS);
            double avgExpValueTD = atof(argv[11]);
            std::exponential_distribution<double> distributionExpTD(avgExpValueTD);
            for (int i = 0; i < nvertici; i++) {
                double TSvalue = 0;
                while (TSvalue == 0) {
                    TSvalue = distributionExpTS(generator);
                }
                serviceTime.push_back(TSvalue);
                std::cout << " mean service time " << serviceTime[i] << std::endl;
            }

            for (int i = 0; i < nvertici; i++) {
                double TDvalue = 0;
                while (TDvalue == 0) {
                    TDvalue = distributionExpTD(generator);
                }
                arrivalTime.push_back(TDvalue);
                std::cout << " mean generation time " << arrivalTime[i] << std::endl;
            }
            break;
        }
        case (2): {
            double constValueTS = atof(argv[10]);
            double constValueTD = atof(argv[11]);

            for (int i = 0; i < nvertici; i++) {
                double TSvalue = constValueTS;
                serviceTime.push_back(TSvalue);
                std::cout << " mean service time " << serviceTime[i] << std::endl;
            }
            for (int i = 0; i < nvertici; i++) {
                double TDvalue = constValueTD;
                arrivalTime.push_back(TDvalue);
                std::cout << " mean generation time " << arrivalTime[i] << std::endl;
            }
            break;

        }
        case (3): {
            double constValueTS = atof(argv[10]);
            double maxUnifValueTD = atof(argv[11]);
            std::uniform_real_distribution<> distributionUnifTD(0, maxUnifValueTD);

            for (int i = 0; i < nvertici; i++) {
                double TSvalue = constValueTS;
                serviceTime.push_back(TSvalue);
                std::cout << " mean service time " << serviceTime[i] << std::endl;
            }

            for (int i = 0; i < nvertici; i++) {
                double TDvalue = 0;
                while (TDvalue == 0) {
                    TDvalue = distributionUnifTD(generator);
                }
                arrivalTime.push_back(TDvalue);
                std::cout << " mean generation time " << arrivalTime[i] << std::endl;
            }

            break;
        }
        case (4): {
            double maxUnifValueTS = atof(argv[10]);
            std::uniform_real_distribution<> distributionUnifTS(0, maxUnifValueTS);
            double constValueTD = atof(argv[11]);


            for (int i = 0; i < nvertici; i++) {
                double TSvalue = 0;
                while (TSvalue == 0) {
                    TSvalue = distributionUnifTS(generator);
                }
                serviceTime.push_back(TSvalue);
                std::cout << " mean service time " << serviceTime[i] << std::endl;
            }

            for (int i = 0; i < nvertici; i++) {
                double TDvalue = constValueTD;
                arrivalTime.push_back(TDvalue);
                std::cout << " mean generation time " << arrivalTime[i] << std::endl;
            }

            break;
        }
    }


    //---------------------------------------------------------
    //adjacency matrix//——————————————————————
    igraph_bool_t connected;
    igraph_matrix_t m;
    igraph_matrix_init(&m, nvertici, nvertici);

//    for(int a = 0; a < nvertici; a ++){
//        for(int b = 0; b < nvertici; b ++){
//            igraph_are_connected(&g1, a, b, &connected);
//            MATRIX(m,a,b) = connected;
//        }
//    }
    //igraph_matrix_print(&m); //print matrix
    double Border1 = 1000.0;//10;//10000.0;//7071.0; //m  1000; //m //Km


    CurrentTime = 0.0;
    //std::cout << "aggiorno pos 1 " << std::endl;

    //adding mobile nodes to the topology
    int speed = atoi(argv[13]); // producer speed
    int seed = atoi(argv[14]); //
    srand(seed);
    for(int i = 0; i < numMob; i++){
        mobile_nodes[i].SetSpeed(speed);
        mobile_nodes[i].SetSpeedDirection((double)(rand() %360) * ((2*PI)/360));
        coord_mobile_nodes->SetCoordinates(Coord_rand(Border1), Coord_rand(Border1));
        mobile_nodes[i].SetPosition(coord_mobile_nodes);
        mobile_nodes[i].initcountMig();

    }
    //std::cout << "aggiorno pos 2 " << std::endl;

    int migrationMode = atoi(argv[15]);
    int failureMode = atoi(argv[16]);
    //int kserverMode = atoi(argv[18]);
    int THRESHOLDMode = atoi(argv[18]);

    if(THRESHOLDMode == 0) {
        THRESHOLD = 0;
    }
    else if(THRESHOLDMode == 1){
        THRESHOLD = 1;
    }



    //    char* migrationMode;
    //    migrationMode = argv[15];
    //    const std::string migrationModeON = "on";
    //    const std::string migrationModeOFF = "off";
    //
    if(migrationMode == 0) {
        migrationMODE = 0;
    }
    else if(migrationMode == 1){
        migrationMODE = 1;
    }

    //    char* failureMode;
    //    failureMode = argv[16];
    //
    //    const std::string failureModeON = "on";
    //    const std::string failureModeOFF = "off";
    //
    if(failureMode == 0) {
        failureMODE = 0;
    }
    else if(failureMode == 1){
        failureMODE = 1;
    }

//    if(kserverMode == 0) {
//        kserverMODE = 0;
//    }
//    else if(kserverMode == 1){
//        kserverMODE = 1;
//    }

    int failedPerc = atoi(argv[17]);
    nodeFail = nvertici*failedPerc/100;
    std::cout << "devono cadere " <<nodeFail << std::endl;
    dec = 1;

//    ev = new Event(FAILURE,2, 0, 0); //10, 0, 0); //event that define the end of the simulation
//    Lista.addEvent(ev);

    ev = new Event(CHECK, 0, 0, 0, 0); //event that define the end of the simulation
    Lista.addEvent(ev);

    return option;
}



int manage::initialize_graph(int argc, char** argv){


    nvertici = atoi(argv[1]); //total number of vertices
    for(int i = 0; i< nvertici; i++) {
        for(int j = 0; j < nvertici; j++){
            Topology[i].initNeighbours();
        }
    }

    for (int i = 0; i< nvertici; i++){
        arrayNvertici.push_back(i);
    }
    //    for (int i = 0; i< arrayNvertici.size(); i++){
    //        std::cout  << "indice : " << arrayNvertici[i] << std::endl;
    //    }

    double id_node[nvertici],x_pos[nvertici], y_pos[nvertici];

    //std::cout << "a" << std::endl;

    //node topology coordinates from file-----------------------------
    std::ifstream file_coord;
    file_coord.open(argv[2]);
    if (!file_coord)                  //test to see if file is open
    {
        std::cout << "Error opening file coordinates" << std::endl;
        return -1;
    }

    else
    {
        for (int i = 0 ; i<nvertici; i ++){
            file_coord >> id_node[i] >> x_pos[i] >> y_pos[i];
            //std::cout << id_node[i] << " " << x_pos[i] << " " << y_pos[i] << std::endl;
        }
    }

    file_coord.close();
    //std::cout << "b" << std::endl;


    //geographic topology creation ------------------------------------------------

    Grafo Topology2;
    for (int i = 0; i<nvertici; i++){
        Topology[i].SetX(x_pos[i]); //m
        Topology[i].SetY(y_pos[i]);
    }



    //std::cout << Topology[0].GetXid() << " " << Topology[0].GetYid() << std::endl;
    //std::cout << "b1" << std::endl;

    //edges from file-----------------------------
    FILE *file_edge = fopen(argv[3], "r" );
    if ( !file_edge )
        return 1;
    else igraph_read_graph_edgelist(&g1, file_edge,
                                    nvertici, 0); //directed graph
    fclose(file_edge);

    //    igraph_vector_t vertices;
    //    igraph_vector_init(&vertices, 0);
    //    igraph_vector_t edges;
    //    igraph_vector_init(&edges, 0);
    //    igraph_get_shortest_path(&g1,&vertices,&edges,0,10,IGRAPH_ALL);

    //std::cout << "c" << std::endl;


    //int nedges = 27;//atoi(argv[7]); //total number of edges


    //weights from file-----------------------------
    //double vec_band[nedges];

    std::ifstream file_band;
    file_band.open(argv[4]);
    if (!file_band)                  //test to see if file is open
    {
        std::cout << "Error opening file bandwidth" << std::endl;
        return -1;
    }

    else
    {
        double temp;
        while(file_band >> temp)
        {

            vec_band.push_back(temp);
        }
        //        for (int i = 0 ; i<nedges; i ++){
        //            file_band >> vec_band[i];
        //            std::cout << vec_band[i] << std::endl;
        //        }

    }

    file_band.close();
    //std::cout << "d" << std::endl;
    nedges = vec_band.size();
    //std::cout << "n edges " << nedges << std::endl;

    //    for (int i = 0 ; i<nedges; i ++){
    //        std::cout << vec_band[i] << std::endl;
    //    }


    //std::cout << "dd" << std::endl;




    //delays from file-----------------------------
    std::ifstream file_delays;
    file_delays.open(argv[5]);
    if (!file_delays)                  //test to see if file is open
    {
        std::cout << "Error opening file delays" << std::endl;
        return -1;
    }

    else
    {
        double temp;
        while(file_delays >> temp)
        {
            vec_delays.push_back(temp);
        }
        //        for (int i = 0 ; i<nedges; i ++){
        //            file_delays >> vec_delays[i];
        //            std::cout << vec_delays[i] << std::endl;
        //        }
    }

    file_delays.close();

    return 0;
}



void manage::update_node_position(){

    for(int i = 0; i < numMob; i++) {
        //std::cout << "nodo mobile " << i << std::endl;
        mobile_nodes[i].UpdatePosition(CurrentTime);
        //std::cout << "update position nodo mobile " << i << std::endl;
        Coordinates *coord_mobile_nodes2;
        coord_mobile_nodes2 = mobile_nodes[i].GetPosition();
        //std::cout << "coord " <<coord_mobile_nodes2->GetCoordinateX() << " " <<  coord_mobile_nodes2->GetCoordinateY() << std::endl;
    }
}



double manage::delayCalculation(int i, int n ){
    double timeMovedtask = 0.0;

    igraph_matrix_t res;
    igraph_bool_t connected;
    igraph_vs_t from;
    igraph_vs_t to;
    from = igraph_vss_1(i);
    to = igraph_vss_1(n);
    //igraph_are_connected(&g1, s, nodeIndex, &res);
    igraph_matrix_init(&res, 0, 0);
    igraph_matrix_print(&res);
    igraph_is_connected(&g1, &connected, IGRAPH_STRONG);
    //    std::cout << "grafo connesso : " << connected << std::endl;
    igraph_shortest_paths(&g1, &res, from, to, IGRAPH_ALL);
    //    std::cout << "distanza : " << MATRIX(res,0,0) << " from " << i << " to " << n << std::endl;
    //    igraph_matrix_print(&res);
    //if(MATRIX(res,0,0) == INFINITY){std::cout << "nodi non connessi inf a: " << std::endl; }
    if(MATRIX(res,0,0) == INFINITY ){ // || MATRIX(res,0,0) == IGRAPH_INFINITY){//} IGRAPH_INFINITY) {
        //        std::cout << "nodi non connessi: " << std::endl;
        timeMovedtask = 10000;
    }
    if(MATRIX(res,0,0) > 0.5 && MATRIX(res,0,0) != INFINITY) {
        //        std::cout << "nodi connessi, posso migrare: " << MATRIX(res,0,0) << std::endl;


        std::vector<igraph_real_t> weights_delay;//[nedges];

        for (int i = 0; i < nedges; i++) {
            weights_delay.push_back(vec_delays[i] * 100);
        }
        //        std::cout << " deletedEdges size " << deletedEdges.size()  << std::endl;

        for(int j = 0; j < deletedEdges.size(); j ++ ) {
            weights_delay.erase(weights_delay.begin() + deletedEdges[j]);
            //            std::cout << " ho cancellato " << deletedEdges[j] << " " << weights_delay[j] << std::endl;
        }
        //        std::cout << " weights_delay.size " << weights_delay.size()  << std::endl;
        igraph_real_t weights_delay2[weights_delay.size()];


        for (int i = 0; i < weights_delay.size(); i++) {
            weights_delay2[i] = weights_delay[i];
            //            std::cout << " delay " << weights_delay2[i] << std::endl;

        }

        igraph_vector_t vertices1;
        igraph_vector_t edges1;
        igraph_vector_init(&vertices1, 0);
        igraph_vector_init(&edges1, 0);

        igraph_vector_view(&weights, weights_delay2, sizeof(weights_delay2) / sizeof(igraph_real_t));
        //        std::cout << " igraph_vector_size(&weights) " << igraph_vector_size(&weights) << std::endl;
        //
        //        std::cout << "numero edge a " << igraph_ecount(&g1) << std::endl;

        igraph_get_shortest_path_dijkstra(&g1, &vertices1, &edges1, i, n, &weights, IGRAPH_ALL);
        //        std::cout << "calcolo i " << i << " n " << n << std::endl; // <<" size " << igraph_vector_size(&vertices1) << "\t" <<   VECTOR(vertices1)[0] <<  "\t" << VECTOR(vertices1)[1] << "\t" << VECTOR(vertices1)[2] <<std::endl;

        for (int b = 0; b < igraph_vector_size(&edges1); b++) {//+1
            int indice = VECTOR(edges1)[b];
            timeMovedtask = timeMovedtask + (vec_delays[indice] / (100 * 100));
            //            std::cout << "delaybrite " << vec_delays[indice] / (100 * 100) <<std::endl;
        }
        //        for (int b = 0; b < nedges; b++) {//+1
        //            std::cout << "delaybrite " << vec_delays[b] / (100 * 100) << std::endl;
        //        }
        igraph_vector_destroy(&edges1);
        igraph_vector_destroy(&vertices1);
    }
    //std::cout << "timeMovedtask " << timeMovedtask << std::endl;

    return timeMovedtask;

}










void manage::migrate(double timeMovedtask, int from, int to, int posQueue, int nodeMob, int idTask){
    Event* ev;
    //std::cout << "migro job  " << idTask << " del nodo mobile  " << nodeMob << std::endl;
    mobile_nodes[nodeMob].setcountMig(idTask);
    //std::cout << "volte che ha migrato il task  " << idTask << " del nodo mobile  " << nodeMob << " " <<  mobile_nodes[nodeMob].getcountMig(idTask) <<  std::endl;



    Topology[from].setSizeQueue(Topology[from].getSizeQueue() - 1);
//    std::cout << " Topology[i].deleteMobileID(posQueue)  " <<  Topology[i].getMobileID(posQueue) << std::endl;
//    std::cout << " Topology[i].deleteJobID(posQueue)  " <<  Topology[i].getJobID(posQueue) << std::endl;

    Topology[from].deleteMobileID(posQueue);
    Topology[from].deleteJobID(posQueue);

    //std::cout << "cancello l'entry in psizione  " << posQueue << std::endl;

    // std::cout << "timeMovedtask " << timeMovedtask << std::endl;
    ev = new Event(ARRIVAL, CurrentTime + timeMovedtask, nodeMob, idTask, to);///add mobile node that generated that task
    //std::cout << "node mob migrate " << nodeMob << std::endl;
    Lista.addEvent(ev); //add to the list of event this one
    Topology[to].setFrequency();
}


void manage::migratePriority(double timeMovedtask, int from, int to, int posQueue, int nodeMob, int idTask){
    Event* ev;
    //std::cout << "migro job  " << idTask << " del nodo mobile  " << nodeMob << std::endl;
    //    std::cout << "id task " << idTask << " è stato generato del nodo " << Topology[i].getMobileID(idTask)  << std::endl;
    mobile_nodes[nodeMob].setcountMig(idTask);
    //std::cout << "volte che ha migrato il task  " << idTask << " del nodo mobile  " << nodeMob << " " <<  mobile_nodes[nodeMob].getcountMig(idTask) <<  std::endl;



    Topology[from].setSizeQueue(Topology[from].getSizeQueue() - 1);
//    std::cout << " Topology[from].deleteMobileID(posQueue)  " <<  Topology[from].getMobileID(posQueue) << std::endl;
//    std::cout << " Topology[from].deleteJobID(posQueue)  " <<  Topology[from].getJobID(posQueue) << std::endl;

    Topology[from].deleteMobileID(posQueue);
    Topology[from].deleteJobID(posQueue);

    //std::cout << "cancello l'entry in psizione  " << posQueue << std::endl;

    // std::cout << "timeMovedtask " << timeMovedtask << std::endl;
    ev = new Event(ARRIVAL_PRIORITY, CurrentTime + timeMovedtask, nodeMob, idTask, to);///add mobile node that generated that task
    //std::cout << "node mob migrate " << nodeMob << std::endl;
    Lista.addEvent(ev); //add to the list of event this one
    Topology[to].setFrequency();



}


bool connectionCheck(int from1, int to1){
    int s;
    bool connessi;
    igraph_matrix_t res;
    igraph_bool_t connected;
    igraph_vs_t from;
    igraph_vs_t to;
    int prove = 0;
    int lengthPath;
    from = igraph_vss_1(from1);
    to = igraph_vss_1(to1);
    //igraph_are_connected(&g1, s, nodeIndex, &res);
    igraph_matrix_init(&res, 1, 1);
    //            igraph_matrix_print(&res);
    igraph_is_connected(&g1, &connected, IGRAPH_STRONG);
    //            std::cout << "grafo connesso : " << connected << std::endl;
    igraph_shortest_paths(&g1, &res, from, to, IGRAPH_ALL);
    if(MATRIX(res,0,0) > 0.5 &&  MATRIX(res,0,0) != IGRAPH_INFINITY) { //if the selected vertex
        // is connected to the failing vertex, the program continues
        //std::cout << "nodi connessi, distanza : " << MATRIX(res,0,0) << std::endl;
        connessi = 1;
    }else{
        connessi = 0;
    }

    return connessi;
}

void manage::check_status(int nodeMob, int option, int argc, char** argv){

    // std::cout << " check " << std::endl;
    double threshold;


    double thresholdBuffer = 0;
    for (int i =0; i< nvertici; i++) {
        if (Topology[i].getState() == 1) {
            //std::cout << " dim " << Topology[i].getSizeQueue() << std::endl;
            //thresholdBuffer = arrivalTime[i]/(serviceTime[i]-arrivalTime[i]);
            //avgTasks.push_back(thresholdBuffer);
            thresholdBuffer = thresholdBuffer + Topology[i].getSizeQueue();
        }
    }
    double threshold1 = thresholdBuffer/(nvertici - failedVertex);//nvertici;
    if(threshold1 > 2){
        threshold = abs(int(-threshold1));
    }
    else if(threshold1 <= 2){
        threshold = 2;
    }

//    std::cout << "soglia " << threshold << std::endl;
//    for (int id = 0; id < nvertici; id++) {
//        std::cout << " numero task nel nodo " << id << " :" << Topology[id].getSizeQueue() << std::endl;
//    }



    int susoglia = 0;
    for (int i =0; i< nvertici; i++) {
        Topology[i].refreshInstantQueueSize();
        Topology[i].setInstantQueueSize(Topology[i].getSizeQueue());
    }


    double timeelab = 0;

    for (int i =0; i< nvertici; i++) {
        //std::cout << "nvertice :" << i << std::endl;

        //if(avgTasks[i] > totavgTasks){
        if(Topology[i].getSizeQueue() > threshold && Topology[i].getState() == 1) {//threshold){ //move all tasks to other nodes with equal probability
            std::cout << "soglia " << threshold << "\t " << i  << "\t " << Topology[i].getSizeQueue() << "\t" << CurrentTime << std::endl;

            sogliasuperata++;
            //std::cout << "node " << i << " has " << Topology[i].getSizeQueue() << " tasks" << std::endl;
            int size = Topology[i].getSizeQueue() - 1; // one task is being processed now
            //std::cout << "size " << size << std::endl;
            //where the tasks move

            modeOffloading = argv[12];

            const std::string uniformMode = "uniform";
            const std::string variableMode = "variable";
            const std::string KSERVERMode = "kserver";

            int offloading;
            if(modeOffloading == uniformMode){
                offloading = 0;
            }
            else if(modeOffloading == variableMode){
                offloading = 1;
            }
            else if(modeOffloading == KSERVERMode){
                offloading = 2;
            }


            switch (offloading) {
                //case 0 uniformMode: the task of the node that overcomes the thresold is migrated with uniform probability
                // to all nodes of the topology

                case 0: {
                    for (int x = size; x >= (1); x--) {
                        if (migrationMODE == 1) {
                            //case 0.1 migration cost on: the task of the node that overcomes the threshold migrates only if
                            // the migration cost of the new nodes is better than the migration cost of the current node
                            timeelab = migrationCostUniformON(nvertici, serviceTime,  x,  i,  timeelab);
                        }else if (migrationMODE == 0) {
                            //case 0.0 migration cost off: the task of the node that overcomes the threshold ALWAYS migrates
                            timeelab = migrationCostUniformOFF(nvertici, serviceTime,  x,  i,  timeelab);
                        }
                    }
                    break;
                }

                    //case 1 variableMode: the task of the node that overcomes the threshold migrates with higher probability
                    // to more powerful nodes of the topology
                case 1: {            //higher probability for the task with higher service time
                    //std::cout << " offloading caso 1: variabile" <<  size << std::endl;

                    for (int x = size; x >= (1); x--) {
                        //std::cout << " posizione " <<     x << " nel nodo  " <<  i << " generato dal nodo mobile " << Topology[i].getMobileID(x) << " task "  << Topology[i].getJobID(x) << std::endl;
                        //case 1.1 migration cost on: the task of the node that overcomes the threshold migrates only if
                        // the migration cost of the new nodes is better than the migration cost of the current node
                        if (migrationMODE == 1) {
                            timeelab = migrationCostVariableON(nvertici, serviceTime,  x,  i,  timeelab);
                        } else if (migrationMODE == 0) {
                            //case 1.0 migration cost off: the task of the node that overcomes the threshold ALWAYS migrates
                            timeelab = migrationCostVariableOFF(nvertici, serviceTime,  x,  i,  timeelab);
                        }
                    }
                    break;
                }
                    //case 2 kserverMODE: the task of the node that overcomes the threshold migrates according the kserver
                    //    problem. This case is used with failures
                case 2:
                {
                    for (int x = size; x >= (1); x--) {
                        //timeelab = migratekserverFailure(i, x, nodeMob, timeelab);
                        if (migrationMODE == 1) {
                            timeelab = migratekserverFailure(i, x, nodeMob, timeelab);
                        } else if (migrationMODE == 0) {
                            //case 1.0 migration cost off: the task of the node that overcomes the threshold ALWAYS migrates
                            timeelab = migrationCostUniformOFF(nvertici, serviceTime,  x,  i,  timeelab);
                        }
                    }
                    break;
                }
            }
            vecThreshold.push_back(threshold);
        }
    }
    //std::cout << " timeelab " << timeelab << std::endl;

    Event *ev;
    ev = new Event(CHECK, CurrentTime+0.5, 0, 0, 0); //event that define the end of the simulation
    Lista.addEvent(ev);
}

double manage::migrationCostVariableON(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab) {
    int n;
//                            bool connessi;
    if (Topology[i].getSizeNeighbours() > 1) {
        //std::cout << "dimensione " << Topology[i].getSizeNeighbours() << std::endl;
        n = preferentialIDgen(i, nvertici, serviceTime);
        //std::cout << "destinazione scelta " << n << std::endl;

        double transmissionCost_new = delayCalculation(i, n);

        if (transmissionCost_new != 10000) {
            timeelab = manageMigrationCost(serviceTime, transmissionCost_new, x, timeelab, n,
                                           i);
        }

    }

    else{
        // std::cout << "i nodi non sono connessi quindi non posso migrare" << std::endl;
        NOconnection++;
        lostTask++;
        int IDmob = Topology[i].getMobileID(x);
        std::cout << "perso " <<  i << "\t" <<   IDmob <<   "\t" <<   Topology[i].getJobID(x) << "\t" << CurrentTime <<std::endl;

        Topology[i].deleteMobileID(x);
        Topology[i].deleteJobID(x);
        mobile_nodes[IDmob].setLostTask();
        Topology[i].setSizeQueue(Topology[i].getSizeQueue() - 1);
    }
    return timeelab;
}




double manage::migrationCostVariableOFF(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab) {
    int n;
//                            bool connessi;
    if(Topology[i].getSizeNeighbours() > 1) {
        //std::cout << "dimensione " << Topology[i].getSizeNeighbours() << std::endl;
        n = preferentialIDgen(i, nvertici, serviceTime);

        //std::cout << "destinazione scelta " << n << std::endl;
        double transmissionCost_new = delayCalculation(i, n);
        if (transmissionCost_new != 10000) {
            migrate(transmissionCost_new + timeelab, i, n, x, Topology[i].getMobileID(x),
                    Topology[i].getJobID(x));
            //std::cout << " il task " << x << " verso il nodo " << n << " e arriver dopo " << transmissionCost_new << " + " <<  (susoglia+size - x) << "* " << 0.1 << std::endl;
            migration++;
            timeelab = timeelab + 0.001;
        }
    }
    else{
        NOconnection++;
        lostTask++;
        int IDmob = Topology[i].getMobileID(x);
        std::cout << "perso " <<  i << "\t" <<   IDmob <<   "\t" <<   Topology[i].getJobID(x) << "\t" << CurrentTime <<std::endl;

        Topology[i].deleteMobileID(x);
        Topology[i].deleteJobID(x);
        mobile_nodes[IDmob].setLostTask();
        Topology[i].setSizeQueue(Topology[i].getSizeQueue() - 1);
    }
    return timeelab;
}



double manage::migrationCostUniformON(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab) {
    int n;
    bool connessi;
    int prove = 0;
    std::uniform_int_distribution<int> distribution(0,nvertici-1);
    if(Topology[i].getSizeNeighbours() > 1) {
        do {
            n = distribution(generator);
        } while (n == i || Topology[n].getState() == 0 || Topology[i].getNeighbours(n) == 0);

        double transmissionCost_new = delayCalculation(i, n);

        if (transmissionCost_new != 10000) {
            timeelab = manageMigrationCost(serviceTime, transmissionCost_new, x, timeelab, n, i);
        }
    }
    else{
        //std::cout << "i nodi non sono connessi quindi non posso migrare" << std::endl;
        NOconnection++;
        lostTask++;
        int IDmob = Topology[i].getMobileID(x);
        std::cout << "perso " <<  i << "\t" <<   IDmob <<   "\t" <<   Topology[i].getJobID(x) << "\t" << CurrentTime <<std::endl;

        Topology[i].deleteMobileID(x);
        Topology[i].deleteJobID(x);
        mobile_nodes[IDmob].setLostTask();
        Topology[i].setSizeQueue(Topology[i].getSizeQueue() - 1);
        //std::cout << " cancello task " <<  << " del nodo mobile " << IDmob << std::endl;
    }
    return timeelab;
}



double manage::migrationCostUniformOFF(int nvertici, std::vector<double> serviceTime, int x, int i, double timeelab) {
    int n;
    std::uniform_int_distribution<int> distribution(0,nvertici-1);
    if(Topology[i].getSizeNeighbours() > 1) {
        do {
            n = distribution(generator);
        } while (n == i || Topology[n].getState() == 0 || Topology[i].getNeighbours(n) == 0);

        //std::cout << "destinazione scelta " << n << std::endl;

        double transmissionCost_new = delayCalculation(i, n);
        if (transmissionCost_new != 10000) {
            migrate(transmissionCost_new + timeelab, i, n, x, Topology[i].getMobileID(x), Topology[i].getJobID(x));
            //std::cout << " il task " << x << " verso il nodo " << n << " e arriver dopo " << transmissionCost_new << " + " <<  (susoglia+size - x) << "* " << 0.1 << std::endl;
            migration++;
            timeelab = timeelab + 0.001;
        }
    }
    else{
        NOconnection++;
        lostTask++;
        int IDmob = Topology[i].getMobileID(x);
        std::cout << "perso " <<  i << "\t" <<   IDmob <<   "\t" <<   Topology[i].getJobID(x) << "\t" << CurrentTime << std::endl;

        Topology[i].deleteMobileID(x);
        Topology[i].deleteJobID(x);
        mobile_nodes[IDmob].setLostTask();
        Topology[i].setSizeQueue(Topology[i].getSizeQueue() - 1);
    }
    return timeelab;
}


double manage::manageMigrationCost(std::vector<double> serviceTime, double transmissionCost_new, int x, double timeelab, int n, int i){

    //std::cout << " instant queue size " <<     n << " " <<     Topology[n].getInstantQueueSize() << " serviceTime[n]/2 " << serviceTime[n]/2 << std::endl;

    double queueCost_new = serviceTime[n]/2 * Topology[n].getInstantQueueSize();
    double elaborationTime_new = timeelab;
    double migrationCost =
            transmissionCost_new + queueCost_new + elaborationTime_new;
    double queueCost_current = serviceTime[i]/2 * (x);
    //std::cout << " queueCost_current =  " << serviceTime[i]/2 <<" * numero task rimanenti " << (x) << " = " << serviceTime[i]/2 * x << ", size "  << Topology[i].getInstantQueueSize() << std::endl;
    double currentCost = queueCost_current;
    //std::cout << " migrationCost = " << migrationCost << " = queueCost_new " << queueCost_new << " Topology[n].getInstantQueueSize() " << Topology[n].getInstantQueueSize() << " + elaborationTime_new " << elaborationTime_new << " + transmissionCost_new " << transmissionCost_new << std::endl;

    //std::cout << " migrationCost " << migrationCost << " currentCost " << currentCost << std::endl;

    if (migrationCost < currentCost) {
        //std::cout << "migro job  " << Topology[i].getJobID(x) << " del nodo mobile  " << Topology[i].getMobileID(x) << std::endl;
        migratePriority(transmissionCost_new + timeelab , i, n, x, Topology[i].getMobileID(x), Topology[i].getJobID(x));
        //std::cout << " il task " << x << " verso il nodo " << n << " e arriver dopo " << transmissionCost_new + timeelab << std::endl;
        migration++;
        Topology[n].setInstantQueueSize(1);
//        std::cout << "instant size coda " << n << " " << Topology[n].getInstantQueueSize() << std::endl;
//        std::cout << " size coda " << n << " " << Topology[n].getSizeQueue() << std::endl;
        Topology[i].decrementInstantQueueSize(1);
//        std::cout << "instant size coda " << i << " " << Topology[i].getInstantQueueSize() << std::endl;
//        std::cout << " size coda " << i << " " << Topology[i].getSizeQueue() << std::endl;
        timeelab=timeelab + 0.001;
        //std::cout << " conviene migrare a " << n << std::endl;
    } else {
        //std::cout << "NON conviene migrare a " << n << " " << CurrentTime << std::endl;
        NOmigration++;
    }
    return timeelab;

}

//a new job is generated by the mobile node (nodeMob)
void manage::generate(int nodeMob, int option,  int argc, char** argv){
    //std::cout << "generate " << nodeMob << "\t" << CurrentTime << std::endl;
    Event *ev;

    Coordinates *coord_mobile_nodes2;
    coord_mobile_nodes2 = mobile_nodes[nodeMob].GetPosition();
    int idClosestRouter = Topology[0].minDistance(Topology, coord_mobile_nodes2, nvertici);
    mobile_nodes[nodeMob].switchID(idClosestRouter);
    mobile_nodes[nodeMob].setJobID();
    mobile_nodes[nodeMob].setcountJob();
    mobile_nodes[nodeMob].initcountMig();

    int currentjobID = mobile_nodes[nodeMob].getcountJob();

    //std::cout << "id task generated : "  << currentjobID << " dal nodo mobile " << nodeMob << " start at " << CurrentTime << std::endl;
    int nextjobID = mobile_nodes[nodeMob].getcountJob()+1;

    // std::cout << "id closest router " <<  idClosestRouter << std::endl;
    //    std::cout << "distanza " << Topology[idClosestRouter].Distance(coord_mobile_nodes2) << std::endl;
    double wirelessDelay = Topology[idClosestRouter].Distance(coord_mobile_nodes2)*1000/ (SPEED_OF_LIGHT); // m/ms
    //    std::cout << "wirelessDistance " <<  Topology[idClosestRouter].Distance(coord_mobile_nodes2) << " wirelessDelay " << wirelessDelay << std::endl;
    ev = new Event(ARRIVAL, CurrentTime + wirelessDelay, nodeMob, currentjobID, idClosestRouter);
    //std::cout << "node mob generate " << nodeMob << std::endl;
    Lista.addEvent(ev);
    //std::cout << "il task arrivera in coda al nodo " << idClosestRouter << " all'istante " << CurrentTime+wirelessDelay << std::endl;

    mobile_nodes[nodeMob].setGenerationTime(CurrentTime);

    int id = mobile_nodes[nodeMob].getID();

    double AT = exponential(arrivalTime[id]);


    ev = new Event(GENERATION, CurrentTime + AT, nodeMob, 0, 0);
    //std::cout << "the next task will be generated  at: " << CurrentTime + AT << " dal nodo " << nodeMob << "sara il task id " << nextjobID << std::endl;
    Lista.addEvent(ev);

    //check_status(0,option, argc, argv );


}

int manage::clock_process(int option,  int argc, char** argv) {
    update_node_position();
    //    std::cout << "clock 1 " << std::endl;

    //    std::cout << "dim lista " << Lista.Size() << std::endl;
    Event *ev;
    ev = Lista.Get(); //get the first event of the list of events
    //std::cout << "clock 2 " << std::endl;
    EventType tipo;
    tipo = ev->type;
    //std::cout << "EventType tipo " << tipo << std::endl;

    //std::cout << "CurrentTime nel clock " << CurrentTime << std::endl;
    CurrentTime = ev->sched_time; //update the current time with the scheduled time at the beginning of the list of events.
    //    std::cout << "CurrentTime in clock process " << CurrentTime << std::endl;
    int mobNode = ev->mobID;
    int switchID = ev->switchID;
    int jobID = ev->jobID;
    //std::cout << "mobNode " << mobNode << "switchID " << switchID << "jobID " << jobID <<std::endl;


    //if(totcompletedTask == (dec)*500/(nodeFail+1)){
    if(totcompletedTask == (dec)*500/(nodeFail+1)){

//        std::cout << " cade un nodo, il numero attuale di task è " << totcompletedTask << std::endl;
        ev = new Event(FAILURE, CurrentTime, 0, 0, 0); //10, 0, 0); //event that define the end of the simulation
        Lista.addEvent(ev);
        dec++;
    }



    switch(tipo)
    {
        case GENERATION:{
            //std::cout << "generate AA" << CurrentTime << std::endl;
            totGeneratedEvent++;
            generate(mobNode, option, argc, argv);
            break;}
        case DEPARTURE:
        {
            //std::cout << "depart AA" << CurrentTime << std::endl;
            depart(mobNode, jobID, option, argc, argv);
            break;
        }
        case ARRIVAL: {
            //std::cout << "arrivo AA" << CurrentTime << std::endl;

            if(Topology[switchID].getState() == 1){
//                std::cout << "arrival " << std::endl;
                arrive(mobNode, jobID, switchID, option, argc, argv);
            }else if(Topology[switchID].getState() == 0)
            {
//                std::cout << "no arrival al " << CurrentTime << " perche il nodo " << switchID << "era caduto " <<  std::endl;
                //Lista.RemoveEvents(ev);
                //std::cout << " evento cancellato " <<  std::endl;

            }
            break;

        }
        case ARRIVAL_PRIORITY: {
            //std::cout << "arrivo AA" << CurrentTime << std::endl;

            //if(Topology[switchID].getState() == 1){
            arrivePriority(mobNode, jobID, switchID, option, argc, argv);
            //}
            break;
        }
        case FAILURE:
        {
            if(failureMODE == 1) {
                //std::cout << "failure AA" << CurrentTime << std::endl;
                failure(option, argc, argv);
            }
            break;
        }

        case CHECK:{
            if(THRESHOLD == 1) {
                check_status(mobNode, option, argc, argv);
            }

            break;
        }


        case SIM_END:
            //Lista.RemoveEvents();
            //std::cout << "End Simulation" << std::endl;
            //destroyVar();
            EndOfSimulation = true;
            break;

    }

    //delete ev;
    //return EndOfSimulation;
    return totcompletedTask;
}



//kserver problem: when a node overcomes the threshold, all its tasks migrate to the node with lower c
// c = migration cost = time spent to move to a node. This value is evaluated for all active node

double manage::migratekserverFailure(int currentID, int queuePosition, int nodeMob, double timeelab){

    int n;
    if(Topology[currentID].getSizeNeighbours() > 1) {
        do {
            n = kserverIDgen(currentID, nvertici, serviceTime, timeelab);
        } while (n == currentID || Topology[n].getState() == 0 || Topology[currentID].getNeighbours(n) == 0);

        //std::cout << "destinazione scelta " << n << std::endl;

        double transmissionCost_new = delayCalculation(currentID, n);
        if (transmissionCost_new != 10000) {
            //MIGRATE or MIFRATEPRIORITY?????
            migrate(transmissionCost_new + timeelab, currentID, n, queuePosition,
                    Topology[currentID].getMobileID(queuePosition), Topology[currentID].getJobID(queuePosition));
            timeelab = timeelab + 0.001;
            migration++;
        }
    }
    else{
        //std::cout << "i nodi non sono connessi quindi non posso migrare" << std::endl;
        NOconnection++;
        lostTask++;
        int IDmob = Topology[currentID].getMobileID(queuePosition);
        std::cout << "perso " <<  currentID << "\t" <<   IDmob <<   "\t" <<   Topology[currentID].getJobID(queuePosition) << "\t" << CurrentTime <<std::endl;

        Topology[currentID].deleteMobileID(queuePosition);
        Topology[currentID].deleteJobID(queuePosition);
        mobile_nodes[IDmob].setLostTask();
        Topology[currentID].setSizeQueue(Topology[currentID].getSizeQueue() - 1);
    }
    return timeelab;
}



//the job (jobID) generated by the mobile node (nodeMob) is served
void manage::depart(int nodeMob, int jobID, int option, int argc, char** argv){


    Event *ev;
    //ev = new Event(DEPARTURE, CurrentTime, nodeMob, 0); //dummy
    for (int i =0; i< nvertici; i++) {
        if (Topology[i].getDeparturetime() == CurrentTime && Topology[i].getState() == 1) {
            std::cout << "fine " << i << "\t " << jobID << "\t " << nodeMob << "\t " << CurrentTime << std::endl;
            //                    std::cout << "nodo " << i << " task " << 0 << " della coda, sizequeue: "<< Topology[i].getSizeQueue() << std::endl;
            //


            //busyTime = busyTime + (CurrentTime - mobile_nodes[nodeMob].getStartTime(jobID));
            double taskLifeTime = CurrentTime - mobile_nodes[nodeMob].getGenerationTime(jobID);
            //std::cout <<  "nodo topo " << i << " taskTime del job " << jobID << " del nodo mobile " << nodeMob << "\t era iniziato a  " << mobile_nodes[nodeMob].getGenerationTime(jobID) << " = " << taskLifeTime << std::endl;
            totLifeTaskTime.push_back(taskLifeTime);
            jobIDLifeTaskTime.push_back(jobID);

            //                    std::cout << " task finito " << std::endl;
            totcompletedTask++;

            Topology[i].deleteMobileID(0);
            Topology[i].deleteJobID(0);

            Topology[i].setSizeQueue(Topology[i].getSizeQueue() -
                                     1); //decrease by 1 the number of tasks in the system because one was completed
            //std::cout <<  "cancello MobileID  e JobID in posizione " << std::endl;
            //std::cout <<  "partenza job " << jobID << " del nodo mobile  " << nodeMob << " dal nodo " << i << " che era iniziato a  " << mobile_nodes[nodeMob].getGenerationTime(jobID) << " = " << taskLifeTime << std::endl;



            if (Topology[i].getSizeQueue() >= 1) {
                double DT = exponential(serviceTime[i]);
                //std::cout << "the next event will depart at " << CurrentTime + DT << " task " << Topology[i].getJobID(0) << " del nodo mobile " << Topology[i].getMobileID(0) << std::endl;
                Topology[i].setDeparturetime(CurrentTime + DT);
                ev = new Event(DEPARTURE, CurrentTime + DT, Topology[i].getMobileID(0), Topology[i].getJobID(0), 0);
                Lista.addEvent(ev);
                //                        std::cout << " ok " << std::endl;

            }

        }
    }
//    check_status(0,option, argc, argv );

}




//the task is moved from a failed node to a less loaded node. Compute the time the task will arrive in the queue. In that time instant the queue size increase
void manage::arrive(int nodeMob, int jobID, int n, int option, int argc, char** argv){
    //double serviceTime = SERV_TIME;
    std::cout << "arrive " << n << " \t" << nodeMob << "\t " << jobID << "\t" << CurrentTime << std::endl;
    //std::cout << " task dell'utente mobile " << nodeMob  << "è arrivato al nodo " << n << std::endl;
    Topology[n].setarriveTime(CurrentTime);
    Event *ev;
    //ev = new Event(DEPARTURE, CurrentTime, nodeMob, 0); //dummy


    Topology[n].setSizeQueue(Topology[n].getSizeQueue() + 1);
    Topology[n].setMobileID(nodeMob);
    Topology[n].setJobID(jobID);
    Topology[n].initStateJob();
    //for(int o = 0; o < Topology[n].getSizeQueue(); o++)
    //std::cout << "task " << o << " è il " << Topology[n].getJobID(o) << " del nodo mobile " << Topology[n].getMobileID(o) << std::endl;

    //if there is just a job in the queue it will be served after DT seconds
    if(Topology[n].getSizeQueue() == 1)
    {
        //std::cout << "dim coda = 1  " << std::endl;
        double DT = exponential(serviceTime[n]);
        //std::cout << "CurrentTime+dt " << CurrentTime+DT << std::endl;
        //std::cout << "getDeparturetimeSize " <<  Topology[n].getDeparturetimeSize() << std::endl;
        double temp = CurrentTime+DT;
        Topology[n].setDeparturetime(temp);
        //std::cout << "CurrentTime " << CurrentTime << std::endl;
        mobile_nodes[nodeMob].setStartTime(CurrentTime);
        //std::cout << "start time del task in coda " <<  mobile_nodes[nodeMob].getStartTime() << std::endl;

        //        std::cout << "there is just one task in the queue of the node " << mobile_nodes[nodeMob].getID() << "and it will depart at " << CurrentTime+DT << "because DT is " << DT << std::endl;

        ev = new Event(DEPARTURE, CurrentTime+DT, nodeMob, jobID, 0);
        Lista.addEvent(ev);
        //std::cout << "partenza inserita " << std::endl;
    }

//    if(THRESHOLD == 1) {
       // check_status(0, option, argc, argv);
//    }





}




void manage::arrivePriority(int nodeMob, int jobID, int n, int option, int argc, char** argv){
    //std::cout << " task dell'utente mobile " << nodeMob  << "è arrivato al nodo " << n << " priority" <<  std::endl;

    Topology[n].setarriveTime(CurrentTime);
    Event *ev;
    int jobPriority = 0;

//controllo lo stato di tutti i job nella coda per trovare la posizione in cui inserire il novo job con priority
// e insierisco il nuovo job dietro agli altri che hanno la priority
    if(Topology[n].getSizeQueue() == 0){
        jobPriority = 0;
    }
    else if(Topology[n].getSizeQueue() > 0 && Topology[n].getStateJob(0) == 0){
        jobPriority = 1;
        for (int y = 0; y < Topology[n].getSizeQueue(); y++) {
            if (Topology[n].getStateJob(y) == 1) {
                jobPriority++;
            }
        }
    }
    else {
        for (int y = 0; y < Topology[n].getSizeQueue(); y++) {
            if (Topology[n].getStateJob(y) == 1) {
                jobPriority++;
            }
        }
    }
    Topology[n].setSizeQueue(Topology[n].getSizeQueue() + 1);

    Topology[n].setMobileIDPriority(nodeMob, jobPriority);
    Topology[n].setJobIDPriority(jobID, jobPriority);
    //setto anche a questo job la priority settando 1 nella nuova posizione introdotta jobPriority
    Topology[n].setStateJob(jobPriority);

    //std::cout << "il nodo " << n << "ha quindi " << Topology[n].getSizeQueue() << " task " << std::endl;
    //for(int o = 0; o < Topology[n].getSizeQueue(); o++)
    //std::cout << "task " << o << " è il " << Topology[n].getJobID(o) << " del nodo mobile " << Topology[n].getMobileID(o) << std::endl;

    //if there is just a job in the queue it will be served after DT seconds
    if(Topology[n].getSizeQueue() == 1)
    {
        //std::cout << "dim coda = 1  " << std::endl;
        double DT = exponential(serviceTime[n]);
        //std::cout << "CurrentTime+dt " << CurrentTime+DT << std::endl;
        //std::cout << "getDeparturetimeSize " <<  Topology[n].getDeparturetimeSize() << std::endl;
        double temp = CurrentTime+DT;
        Topology[n].setDeparturetime(temp);
        //std::cout << "CurrentTime " << CurrentTime << std::endl;
        mobile_nodes[nodeMob].setStartTime(CurrentTime);
        //std::cout << "start time del task in coda " <<  mobile_nodes[nodeMob].getStartTime() << std::endl;

        //        std::cout << "there is just one task in the queue of the node " << mobile_nodes[nodeMob].getID() << "and it will depart at " << CurrentTime+DT << "because DT is " << DT << std::endl;

        ev = new Event(DEPARTURE, CurrentTime+DT, nodeMob, jobID, 0);
        Lista.addEvent(ev);
        //std::cout << "partenza inserita " << std::endl;
    }

//    if(THRESHOLD == 1) {
       // check_status(0, option, argc, argv);
//    }




}


void manage::destroyVar() {
    delete [] mobile_nodes;
    delete coord_mobile_nodes;

}


//igraph_real_t<int, 5> weightsFunction(std::vector<double> vec_delays, int nedges){
//    igraph_real_t weights_delay[nedges];
//    for(int i = 0; i<nedges; i++){
//        weights_delay[i] = vec_delays[i]*100;
//        std::cout << weights_delay[i] << std::endl;
//
//    }
//    return weights_delay;
//};

void manage::destroyGraph(){
    igraph_destroy(&g1);
}


void manage::failure( int option, int argc, char** argv) {
    //the id of the node that will fail is RANDOMLY chosen among the vertices still active if variable or uniform mode
    const std::string uniformMode = "uniform";
    const std::string variableMode = "variable";
    const std::string KSERVERMode = "kserver";

    int n;
    int failurenodeId;
    modeOffloading = argv[12];

    //the id of the node that will fail is chosen among the more powerful vertices still active if kserver mode
    if (modeOffloading == uniformMode || modeOffloading == variableMode) {
        n = randId(arrayNvertici.size());
        failurenodeId = arrayNvertici[n];
    } else if (modeOffloading == KSERVERMode) {
        failurenodeId = powerfulIDgen(nvertici, serviceTime);
    }

    //arrayNvertici saves the vertices still active



    for (int q = 0; q < nvertici; q++){
        for(int p = 0; p < nvertici; p++) {
            if (Topology[q].getState() == 1 && Topology[p].getState() == 1) {
                int connessi = connectionCheck(p, q);
                Topology[q].setNeighbours(p, connessi);
            }
            else if (Topology[q].getState() == 0 || Topology[p].getState() == 0){
                Topology[q].setNeighbours(p, 0);
            }
        }
    }

    // std::cout << " cade nodo: " << failurenodeId <<  std::endl; //" size " << arrayNvertici.size() << std::endl;

    igraph_vector_t eids;
    igraph_vector_init(&eids, 0);
    igraph_es_t eids2;
    igraph_es_none(&eids2);

    //    std::cout << " time : " << time << std::endl;
    //all the tasks of the failed node migrate
    int size = Topology[failurenodeId].getSizeQueue() - 1; // all tasks index from 0 to SizeQueue()-1
    std::cout << " failure " << failurenodeId << "  failedVertex " << failedVertex << " \t" << CurrentTime <<  std::endl;
    std::uniform_int_distribution<int> distribution(0, nvertici - 1);
    //update the number of failed vertices
    failedVertex++;
    double timeelab = 0;

    for (int x = size; x > (0); x--) {
        //std::cout << "task numero " << x << std::endl;
        int s;
        igraph_matrix_t res;
        igraph_bool_t connected;
        igraph_vs_t from;
        igraph_vs_t to;
        int prove = 0;
        int lengthPath;
        do {
            do {
                //if uniformMode, the vertex where the tasks migrate to is uniformly chosen among the active nodes
                if (modeOffloading == uniformMode) {
                    s = distribution(generator);
                    //std::cout << "proposed vertex " << s << std::endl;
                }
                    //if variableMode, the vertex where the tasks migrate to is chosen among the more powerful active nodes
                else if (modeOffloading == variableMode) {
                    if(Topology[failurenodeId].getSizeNeighbours() > 1) {
                        //std::cout << "dimensione vicinato " << Topology[failurenodeId].getSizeNeighbours() << std::endl;
//                        for(int q = 0; q < nvertici; q++){
//                            std::cout << "vicino " << Topology[failurenodeId].getNeighbours(q) << std::endl;
//                        }
                        s = preferentialIDgen(failurenodeId, nvertici, serviceTime);
                        //std::cout << "proposed vertex " << s << std::endl;
                    }
                    else{
                        s = distribution(generator);
                    }
                }
                    //if KSERVERMode, the vertex where the tasks migrate to is chosen according kserver AGGIUSTA!!!!!!
                else if (modeOffloading == KSERVERMode) {
                    if(Topology[failurenodeId].getSizeNeighbours() > 1) {
                        s = kserverIDgen(failurenodeId, nvertici, serviceTime, timeelab);
                    }
                    else{
                        s = distribution(generator);
                    }
                }
                prove++;
            } while (failurenodeId == s || Topology[s].getState() == 0);// && Topology[n].getSizeQueue() >= threshold);
            //std::cout << "chosen vertex " << s << std::endl;

            //std::cout << "sposto dal nodo " << " al nodo: " << s <<  std::endl;
            from = igraph_vss_1(failurenodeId);
            to = igraph_vss_1(s);
            //igraph_are_connected(&g1, s, nodeIndex, &res);
            igraph_matrix_init(&res, 1, 1);
            //            igraph_matrix_print(&res);
            igraph_is_connected(&g1, &connected, IGRAPH_STRONG);
            //            std::cout << "grafo connesso : " << connected << std::endl;
            igraph_shortest_paths(&g1, &res, from, to, IGRAPH_ALL);
            //            std::cout << "distanza : " << MATRIX(res,0,0) << std::endl;
            //            igraph_matrix_print(&res);
//                        if(MATRIX(res,0,0) == IGRAPH_INFINITY) {
//                            std::cout << "nodi non connessi: " << std::endl;
//                        }
            if (MATRIX(res, 0, 0) > 0.5 && MATRIX(res, 0, 0) != IGRAPH_INFINITY) { //if the selected vertex
                // is connected to the failing vertex, the program continues
                //std::cout << "nodi connessi, distanza : " << MATRIX(res, 0, 0) << std::endl;
                break;
            }
        } while (prove < nvertici); //lengthPath == 0
        if (MATRIX(res, 0, 0) > 0.5 && MATRIX(res, 0, 0) != IGRAPH_INFINITY) {
            //if the selected vertex is connected to the failing vertex, the task migrate
            double transmissionCost_new = delayCalculation(failurenodeId, s);
            migrate(transmissionCost_new + timeelab, failurenodeId, s, x, Topology[failurenodeId].getMobileID(x),
                    Topology[failurenodeId].getJobID(x));
            //std::cout << " migra il task " << x << " verso il nodo " << n << " e arriverà dopo " << transmissionCost_new << " + " <<  (size - x) << " " << 0.1 << std::endl;
            // std::cout << "task spostato" << std::endl;
            Topology[failurenodeId].setMobileID(size);
            migration++;
            timeelab = timeelab + 0.001;
        } else {
            //if the selected vertex is NOT connected to the failing vertex, the task is lost
            lostTask++;

            int IDmob = Topology[failurenodeId].getMobileID(x);
            std::cout << "perso " <<  failurenodeId << "\t" <<   IDmob <<   "\t" <<   Topology[failurenodeId].getJobID(x) << "\t" << CurrentTime <<std::endl;

            Topology[failurenodeId].deleteMobileID(x);
            Topology[failurenodeId].deleteJobID(x);
            mobile_nodes[IDmob].setLostTask();
            Topology[failurenodeId].setSizeQueue(Topology[failurenodeId].getSizeQueue() -
                                                 1);
        }
        igraph_matrix_destroy(&res);
    }
    //remove the edges that connect the failing nodes to the other vertices
    igraph_incident(&g1, &eids, failurenodeId, IGRAPH_ALL);
    for (int i = 0; i < igraph_vector_size(&eids); i++) {
        //std::cout << "edge : " <<  VECTOR(eids)[i] << std::endl;
        deletedEdges.push_back(VECTOR(eids)[i]);
    }
    std::sort(deletedEdges.rbegin(), deletedEdges.rend());

    igraph_es_vector_copy(&eids2, &eids);
    igraph_delete_edges(&g1, eids2);
    // std::cout << "qui 1 " << "failurenodeId " << failurenodeId << std::endl;

    //update arrayNvertici by deleting the failed node
    int IDtodelete = 0;
    for (int i = 0; i < arrayNvertici.size(); i++) {
        if (arrayNvertici[i] == failurenodeId) {
            IDtodelete = i;
        }
    }
    arrayNvertici.erase(arrayNvertici.begin() + (IDtodelete));

//    for(int i = 0; i< arrayNvertici.size(); i++){
//        //        std::cout << "indice nodi ancora vivi " << arrayNvertici[i] << std::endl;
//    }
    //set the state of the failed node to 0 (0 = failed, 1 = active)
    Topology[failurenodeId].setState(0);

// set the vertices that each node can reach because it is connected to them
    for (int q = 0; q < nvertici; q++){
        for(int p = 0; p < nvertici; p++) {
//            igraph_vector_ptr_t res;
//            igraph_vs_t vid = igraph_vss_1(arrayNvertici[q]);
//            igraph_neighborhood(&g1, &res, vid, 1, IGRAPH_ALL);
            if (Topology[q].getState() == 1 && Topology[p].getState() == 1) {
                int connessi = connectionCheck(p, q);
                //std::cout << " connessi " << connessi << std::endl;

                Topology[q].setNeighbours(p, connessi);
            }
            else if (Topology[q].getState() == 0 || Topology[p].getState() == 0){
                Topology[q].setNeighbours(p, 0);
            }
        }
    }

}




void manage::statistics(){
    double c = totcompletedTask/simulationTime;
    //double b = busyTime/simulationTime;
    double totLifeTimeTask = 0;
    for (int i = 0; i < totLifeTaskTime.size(); i++){
        //std::cout << "durata task: " << i << " " <<totLifeTaskTime[i]<< std::endl;
        totLifeTimeTask = totLifeTimeTask + totLifeTaskTime[i];
    }
    int jobIDtotLifeTimeTask = 0;
    std::vector<int> freq_id;
    for (int num = 0; num < 100; num++) {
        freq_id.push_back(0);
    }
    for (int i = 0; i < jobIDLifeTaskTime.size(); i++){
        //std::cout << "job id task: " << i << " " <<jobIDLifeTaskTime[i]<< std::endl;

        jobIDtotLifeTimeTask = jobIDtotLifeTimeTask + jobIDLifeTaskTime[i];
        for (int num = 0; num < 100; num++) {
            if (jobIDLifeTaskTime[i] == num){
                freq_id[num] = freq_id[num] + 1;
            }
        }
    }

//    for (int num = 0; num < 100; num++) {
//        std::cout << "freq job id : " << num << " " <<freq_id[num]<< std::endl;
//
//    }

    double sogliaMedia = 0;
    for (int i = 0; i < vecThreshold.size(); i++){
        sogliaMedia = sogliaMedia + vecThreshold[i];
    }
    sogliaMedia = sogliaMedia/vecThreshold.size();


    std::cout << "Simulation: " << CurrentTime << std::endl;
    std::cout << "totLifeTaskTime size: " <<totLifeTaskTime.size()<< std::endl;
    std::cout << "Events tot: " << totGeneratedEvent << std::endl;
    std::cout << "Time completed tasks: " << totLifeTimeTask << std::endl;
    std::cout << "tempo medio di un task: " << totLifeTimeTask/500 << std::endl;

    std::cout << "Completed tasks: " << totcompletedTask << std::endl;
    std::cout << "Throughput rate: " << c << std::endl;
    std::cout << "Server utilization rate: " << (totcompletedTask/simulationTime)*100 << std::endl;
    std::cout << "lost tasks " << lostTask << std::endl;
    std::cout << "migrated tasks " << migration << std::endl;
    std::cout << "NOmigrated tasks " << NOmigration << std::endl;
    std::cout << "NOconnected tasks " << NOconnection << std::endl;
    std::cout << "numero volte soglia superata " <<sogliasuperata << std::endl;

    std::cout << "soglia media " << sogliaMedia << std::endl;

//    for(int i = 0; i < numMob; i ++){
//        for (int j = 0; j < mobile_nodes[i].getnumMigSize(); j++){
//            if(mobile_nodes[i].getcountMig(j) != 0){
//                std::cout << "numero mig del task: " << j << " del nodo mobile " << i << " : " << mobile_nodes[i].getcountMig(j) << std::endl;
//            }
//        }
//    }


    for(int i = 0; i < nvertici; i ++){
        std::cout << "Freq: " << i << "\t" << Topology[i].getFrequency() << std::endl;
    }

    //RIVEDERE QUESTO!!!

    std::vector<std::vector<double>> arrayArriveTime;
    for(int i = 0; i < nvertici; i++) {
        std::vector<double> temp; // create an array, don't work directly on buff yet.
        for (int j = 1; j < Topology[i].getarriveTimeSize(); j++) {
            temp.push_back(Topology[i].getarriveTime(j) - Topology[i].getarriveTime(j-1));
        }
        arrayArriveTime.push_back(temp); // Store the array in the buffer
    }


    std::vector<double> averageArriveTime;
    for(int i = 0; i < nvertici; i ++) {
        averageArriveTime.push_back(0);
    }
    for(int i = 0; i < nvertici; i ++){
        for(int j = 0; j < Topology[i].getarriveTimeSize()-1; j ++) {
            averageArriveTime[i] = averageArriveTime[i] + arrayArriveTime[i][j];
        }
        if(averageArriveTime[i] != 0){
            std::cout << "Avg arrival: " << i << " \t " << averageArriveTime[i]/Topology[i].getarriveTimeSize() << std::endl;
        }
        else{
            std::cout << "Avg arrival: " << i << " \t " << averageArriveTime[i] << std::endl;

        }

    }

//RIVEDERE QUESTO!!!
//    for (int i = 0; i < numMob; i ++) {
//        std::cout << "mob lost: " << i << "\t" << mobile_nodes[i].getLostTask() << std::endl;
//    }




    std::cout << "fine: " << std::endl;


}