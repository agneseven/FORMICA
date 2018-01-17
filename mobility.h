//
// Created by A on 10/10/17.
//

#ifndef QUEUE_PROVA2_MOBILITY_H
#define QUEUE_PROVA2_MOBILITY_H

#include "Coordinates.h"


class Mobility {
    Coordinates *Position;
    int m_speed;			 		// Km/h
    double m_speedDirection;	 	// radianti
    double m_positionLastUpdate;
public:
    Mobility();
    virtual ~Mobility();
    void SetPosition (Coordinates *position);
    Coordinates* GetPosition (void) const;
    void DeletePosition (void);

    virtual void UpdatePosition (double time) = 0;

    void SetSpeed (int speed);
    int GetSpeed (void) const;
    void SetSpeedDirection (double speedDirection);
    double GetSpeedDirection (void) const;

    void SetPositionLastUpdate (double time);
    double GetPositionLastUpdate (void) const;
};


#endif //QUEUE_PROVA2_MOBILITY_H
