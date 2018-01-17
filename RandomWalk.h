//
// Created by A on 10/10/17.
//

#ifndef QUEUE_PROVA2_RANDOMWALK_H
#define QUEUE_PROVA2_RANDOMWALK_H

#include "mobility.h"

class RandomWalk:public Mobility {

    double m_interval;
    double m_lastTimeDirectionChange;
public:
    RandomWalk();
    ~RandomWalk();

    void UpdatePosition (double time);

};


#endif //QUEUE_PROVA2_RANDOMWALK_H
