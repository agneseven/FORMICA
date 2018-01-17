//
// Created by A on 17/10/17.
//

#ifndef QUEUE_PROVA2_MOBILENODE_H
#define QUEUE_PROVA2_MOBILENODE_H
#include "RandomWalk.h"
#include <vector>


class mobileNode:public RandomWalk{

    int nodeId;
    double startTime;
    std::vector<double> genTime;
    std::vector<int> genTask;
    std::vector<int> switchTask;
    int lostTasks;

    std::vector<int> JobID;
    int totJobID;
    std::vector<int> numMig;


public:
    mobileNode();
    ~mobileNode();
    void switchID(int ID);
    int getID();
    void setJobID();

    void setcountJob();
    int getcountJob();

    void setcountMig(int ID);
    int getcountMig(int ID);
    int getnumMigSize();
    void initcountMig();






    void setStartTime(double start);
    double getStartTime();

    void setGenerationTime(double generationTime);
    double getGenerationTime(int taskID);

    void setgenTask(int taskID);
    int getgenTask(int ID);

    void setswitchTask(int switchID);
    int getswitchTask(int ID);

    void setLostTask();
    int getLostTask();



};


#endif //QUEUE_PROVA2_MOBILENODE_H
