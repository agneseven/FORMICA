//
// Created by A on 16/10/17.
//

#include "event_list.h"
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>



struct CompareEventTime {
    bool operator()(Event * lhs, Event * rhs) {return lhs->sched_time < rhs->sched_time;}
};



//struct CompareEventTime {
//bool sort_by_time(const Event &a, const Event &b) { return a.sched_time < b.sched_time; }
//bool operator()(Event * lhs, Event * rhs){return lhs->sched_time <= rhs->sched_time;}
//
//};
//    bool operator<(Event const &lhs, Event const &rhs) {
//        return lhs.sched_time < rhs.sched_time;
//    }
//};


////add an event in the list of events
void event_list::addEvent(Event *ev){
    std::list<Event*>::iterator it = ev_list.begin();
//    std::cout << "add event " << std::endl;
//    std::cout << "ev->sched_time " << ev->sched_time << std::endl;
//    std::list<Event*>::iterator it2;
//    //for(;(it != ev_list.end())&&((*it)->sched_time <= ev->sched_time);++it)
//    for(it = ev_list.begin(); (it != ev_list.end());++it)
//    {
//
//        if((*it)->sched_time <= ev->sched_time)
//            it2 = it;
//    }
    //{
    //std::cout << "evento inserito in posizione " << it << std::endl;

    //ev_list.insert(it2,ev);
    ev_list.push_back(ev);
    //std::cout << "inserito evento nella lista" << std::endl;

    //std::sort(ev_list, ev_list.size(), sort_by_time);

    ev_list.sort(CompareEventTime());


//    ev_list.sort(CompareEventTime());

//    std::priority_queue<double, std::vector<double>, std::less<double>> q1;
//    for (int i=0; i<ev_list.size(); ++i)
//    {
//        q1.push(ev_list[i].);
//    }
//    std::cout << "q1: ";
//    for (; !q1.empty(); q1.pop())
//        std::cout << q1.top() << ' ';
//    std::cout << '\n';


    //}
    //std::cout << "ordinato evento nella lista" << std::endl;

    //for (std::list<Event*>::iterator i=ev_list.begin(); i!=ev_list.end(); i++)
    //std::cout << (*i)->sched_time << std::endl;


    //std::cout << "fine elenco task " << std::endl;


};







int event_list::Size(){
    //std::cout << "size " << std::endl;


    int sizelist = ev_list.size();

    return sizelist;

};


//get the fist event in the list
Event *event_list::Get(){
    //std::cout << "get first element of the list " << std::endl;
    if(ev_list.empty()) {
        //std::cout << "null" << std::endl;
        return NULL;
    }

    Event *ev = ev_list.front();
    EventType tipo;
    tipo = ev->type;
    //std::cout << "tipo " << tipo << std::endl;
    ev_list.pop_front();
    //std::cout << "ho eliminato l'elemento estratto " << std::endl;

    return ev;

};

//get the fist event in the list
//    double event_list::Get2(int j){
//    if(ev_list.empty()) {
//        std::cout << "null" << std::endl;
//        return NULL;
//    }
//
//    std::list<Event *, std::__1::allocator<Event *>>::iterator ev = ev_list.begin()+j;
//
//    return (*ev)->sched_time;
//
//};

//remove the event from the list
void event_list::RemoveEvents(Event* evento){
//    std::list<Event*>::iterator it = ev_list.begin() ;
//    while((*it)->type != ARRIVAL)
//        it++;
//    ev_list.erase(it);
//    auto one_after_start = ev_list.begin();
//    std::advance(one_after_start, +1); // or --one_before_end;
//    while (it != one_after_start) ev_list.erase(it++);

    for (std::list<Event*>::iterator i=ev_list.begin(); i!=ev_list.end(); i++){

        if((*i)->sched_time == evento->sched_time && (*i)->type == evento->type && (*i)->mobID == evento->mobID && (*i)->switchID == evento->switchID){
            std::cout <<"cancello " << std::endl;
            ev_list.erase(i);
        }
    }

//    for (std::list<Event*>::iterator i=ev_list.begin(); i!=ev_list.end(); i++)
//        std::cout << (*i)->sched_time << std::endl;


};

//test to check the status of the list: T if the list is empty, F otherwise
bool event_list::Empty(){
    if(ev_list.empty())
        return true;
    else
        return false;

};
