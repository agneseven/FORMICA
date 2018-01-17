//
// Created by A on 17/10/17.
//

#include "mobileNode.h"


mobileNode::mobileNode()
{
//    SetSpeed (0);
//    SetSpeedDirection (0.0);
//    SetPositionLastUpdate (0.0);
//
//    SetPosition (NULL);
//    m_interval = 0.;
//    m_lastTimeDirectionChange = 0.;
    lostTasks = 0;
    totJobID = 0;

};

mobileNode::~mobileNode()
{
    //DeletePosition();
}


void mobileNode::switchID(int ID){

    nodeId = ID;
}


int mobileNode::getID(){

    return nodeId;
}

void mobileNode::setJobID(){

    JobID.push_back(1);
}
//int mobileNode::getJobID(jobID);
//
//    return JobID;
//}
void mobileNode::setcountJob(){
    totJobID ++;
}

int mobileNode::getcountJob(){
    return (totJobID-1);
}


void mobileNode::setcountMig(int ID){
    numMig[ID] = numMig[ID] +1 ;
}
void mobileNode::initcountMig(){
    numMig.push_back(0);
}
int mobileNode::getcountMig(int ID){
    return (numMig[ID]);
}

int mobileNode::getnumMigSize(){
    return numMig.size();
}


void mobileNode::setStartTime(double start){
    startTime = start;

};
double mobileNode::getStartTime(){
    return startTime;
};


void mobileNode::setGenerationTime(double generationTime){
    genTime.push_back(generationTime);
};
double mobileNode::getGenerationTime(int taskID){
    return genTime[taskID];
};

void mobileNode::setgenTask(int taskID){
    genTask.push_back(taskID);
};
int mobileNode::getgenTask(int ID){
    return genTask[ID];
};

void mobileNode::setswitchTask(int switchID){
    switchTask.push_back(switchID);
};
int mobileNode::getswitchTask(int ID){
    return switchTask[ID];
};

void mobileNode::setLostTask(){
    lostTasks = lostTasks + 1;
};
int mobileNode::getLostTask(){
    return lostTasks;
};
