//
// Created by A on 10/10/17.
//

#ifndef QUEUE_PROVA2_GRAFO_H
#define QUEUE_PROVA2_GRAFO_H

#include "Coordinates.h"
#include <cmath>
#include <vector>
#include "igraph.h"



class Grafo:public Coordinates {
    //int n_id;
    //double xpos;
    //double ypos;
    Coordinates *nodi_pos;
    int queueSize;
    int InstantqueueSize;

    bool state;
    int frequency;
    std::vector<double> arriveTime;
    double departureTime;
    std::vector<int> mobileID;
    std::vector<int> JobID;
    std::vector<int> StateJob;
    std::vector<int> listNeighbours;


public:
    Grafo();//(int idn);//, double x, double y);
    ~Grafo();
    //void CreateGrafo(int i, double x, double y);
    void SetX(double X);
    void SetY(double Y);
    double GetXid();
    double GetYid();
    //int GetYid();
    double Distance(Coordinates *remoteObject);
    int minDistance(Grafo g[], Coordinates *coord2, int N);
    void setSizeQueue(int size);
    int getSizeQueue();
    void setInstantQueueSize(int sizeIncrement);
    void decrementInstantQueueSize(int sizeIncrement);
    int getInstantQueueSize();
    void refreshInstantQueueSize();



    void setarriveTime(double arrive);
    double getarriveTime(int id);
    void deletearriveTime(int j);
    int getarriveTimeSize();

    void setDeparturetime(double departure);
    double getDeparturetime();

    void setState (bool newstate);
    bool getState();
//    int getDeparturetimeSize();
//    void deleteDeparturetime(int j);
    void setFrequency ();
    int getFrequency();

    void setMobileID(int nodeMob);
    void deleteMobileID(int idTask);
    int getMobileID(int id);
    void setMobileIDPriority(int nodeMob, int pos );


        void setJobID(int jobid);
    int getJobID(int jobid);
    void deleteJobID(int idTask);
    void setJobIDPriority(int nodeMob, int pos );

    void initStateJob();
    void setStateJob(int id);
    int getStateJob(int id);


    void initNeighbours();
    void setNeighbours(int id, int connessi);
    int getNeighbours(int id);
    int getSizeNeighbours();



    };

static double GetTopology_Border (void)
{
    static double border = 10000.0;//10.0;
    return (border);

}



#endif //QUEUE_PROVA2_GRAFO_H
