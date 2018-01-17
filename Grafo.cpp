//
// Created by A on 10/10/17.
//

#include "Grafo.h"
#include <iostream>


void Grafo::SetX(double X)
{
    nodi_pos->SetCoordinateX(X);

}

void Grafo::SetY(double Y)
{
    nodi_pos->SetCoordinateY(Y);
}


Grafo::Grafo(){//(int idn) {//, double x, double y){
    //n_id = idn;
    //xpos = x;
    //ypos = y;
    nodi_pos = new Coordinates ();
    queueSize = 0;
    state = 1;


    //nodi_pos->SetCoordinateX(x);
    //nodi_pos->SetCoordinateY(y);
}


Grafo::~Grafo(){
    delete nodi_pos;
};

double Grafo::GetXid(){
    return nodi_pos->GetCoordinateX();
    //return xpos;
}
double Grafo::GetYid(){
    return nodi_pos->GetCoordinateY();
    //return ypos;
}

double Grafo::Distance(Coordinates *remoteObject)
{
    /*
     * Computes distance from this object and remoteObject
     */
    return
            sqrt (pow ((nodi_pos->GetCoordinateX() - remoteObject->GetCoordinateX()),2) +
                  pow ( (nodi_pos -> GetCoordinateY() - remoteObject->GetCoordinateY()) ,2));

}

int Grafo::minDistance(Grafo g[], Coordinates *coord2, int n){

    int N = n;
    double array_dist[N];

    for (int i = 0; i<N; i++){
        array_dist[i] = g[i].Distance(coord2);
        //std::cout << array_dist[i] << std::endl;
    }

    //the topology node nearest to the modilbe node, it is chosen as attachment point
    double min;
    int att_point_id;
    for (int i = 0; i < N; ++i) {
        if(g[i].getState() == 1){
            min = array_dist[i];
            //std::cout << "i " << i << " " << g[i].getState() << std::endl;
            att_point_id = i;
        }
    }



    for (int i = 0; i < N; ++i) {
        //std::cout << "stato nodo " << i << " " << g[i].getState() << std::endl;
        if (array_dist[i] < min){
            if(g[i].getState() == 1) {
                min = array_dist[i];
                att_point_id = i;
            }
        }
    }
    //std::cout << "The nearest node is'" << std::endl;
    //std::cout << "att_point_id " << att_point_id << " " << g[att_point_id].getState() << std::endl;



    return att_point_id;
}

void Grafo::setSizeQueue(int size){
    queueSize = size;
}

int Grafo::getSizeQueue(){

    return queueSize;

}



void Grafo::setInstantQueueSize(int sizeIncrement){
    InstantqueueSize = InstantqueueSize + sizeIncrement;
}
void Grafo::decrementInstantQueueSize(int sizeIncrement){
    InstantqueueSize = InstantqueueSize - sizeIncrement;
}


void Grafo::refreshInstantQueueSize(){
    InstantqueueSize = 0;
}

int Grafo::getInstantQueueSize(){

    return InstantqueueSize;

}

void Grafo::setarriveTime(double arrive){
    arriveTime.push_back(arrive);
};
double Grafo::getarriveTime(int id){
    return arriveTime[id];
};
void Grafo::deletearriveTime(int j){
    arriveTime.erase(arriveTime.begin() + j-1);
};

int Grafo::getarriveTimeSize(){
    return arriveTime.size();

}

void Grafo::setDeparturetime(double depart){
    departureTime = depart;
};
double Grafo::getDeparturetime(){
    return departureTime;
};

//int Grafo::getDeparturetimeSize(){
//    return departureTime.size();
//}

//void Grafo::deleteDeparturetime(int j) {
//    departureTime.erase(departureTime.begin() + j-1);
//}

void Grafo::setState (bool newstate){
    state = newstate;
};
bool Grafo::getState(){
    return state;
};


void Grafo::setFrequency (){
    frequency++;
};
int Grafo::getFrequency(){
    return frequency;
};

void Grafo::setMobileID(int nodeMob){
    mobileID.push_back(nodeMob);
};

void Grafo::setMobileIDPriority(int nodeMob, int pos ){
    std::vector<int>::iterator it;

    if(mobileID.size() == 0){
        it = mobileID.begin();
        mobileID.insert ( it , nodeMob );
    }else{
        it = mobileID.begin();
        mobileID.insert ( it+pos , nodeMob );
    }
};

void Grafo::deleteMobileID(int idTask){
    mobileID.erase(mobileID.begin()+idTask);
};

int Grafo::getMobileID(int id){
    return mobileID[id];
}

void Grafo::setJobID(int jobid){
    JobID.push_back(jobid);
}



void Grafo::setJobIDPriority(int jobid, int pos ){
    std::vector<int>::iterator it;
    if(JobID.size() == 0){
        it = JobID.begin();
        JobID.insert ( it , jobid );
    }else{
        it = JobID.begin();
        JobID.emplace ( it+pos , jobid );
            }
};


int Grafo::getJobID(int jobid){
    return JobID[jobid];
}

void Grafo::deleteJobID(int idTask){
    JobID.erase(JobID.begin()+idTask);
};


void Grafo::initStateJob(){
    StateJob.push_back(0);
};
void Grafo::setStateJob(int id){
    std::vector<int>::iterator it;
    it = StateJob.begin();
    StateJob.insert(it+id, 1);
};

int Grafo::getStateJob(int id){
    return StateJob[id];
};


void Grafo::initNeighbours(){
        listNeighbours.push_back(1);
}

void Grafo::setNeighbours(int id, int connessi){
    listNeighbours[id] = connessi;
}

int Grafo::getNeighbours(int id){
    return listNeighbours[id];
}

int Grafo::getSizeNeighbours(){
    int dim = 0;
    for(int q = 0; q < listNeighbours.size(); q++){
        if(listNeighbours[q] == 1)
            dim = dim +1;
    }
    return dim;
}
