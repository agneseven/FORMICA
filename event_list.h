//
// Created by A on 16/10/17.
//

#ifndef QUEUE_PROVA2_EVENT_LIST_H
#define QUEUE_PROVA2_EVENT_LIST_H

#include <list>

enum EventType{GENERATION, ARRIVAL, ARRIVAL_PRIORITY, DEPARTURE, FAILURE, CHECK, SIM_END};

class Event{
public:
    EventType type; //type of the event
    double sched_time; // time instance of the event
    int mobID;
    int switchID;
    int jobID;
    inline Event(enum EventType tipo, double time, int IDmob, int IDjob, int IDswitch){
        type = tipo;
        sched_time = time;
        mobID = IDmob;
        switchID = IDswitch;
        jobID = IDjob;


    }; //constructor

};


class event_list {
    std::list<Event*> ev_list; //list of the event
public:
    inline event_list(){
    }; //constructor
    inline ~event_list(){
    }; //constructor
    void addEvent(Event *ev); //add an event in the list of events
    Event *Get(); //get the fist event in the list
    void RemoveEvents(Event* evento); //remove the event from the list
    bool Empty(); //test to check the status of the list: T if the list is empty, otherwise
    int Size();
//        double Get2(int j);

};


#endif //QUEUE_PROVA2_EVENT_LIST_H
