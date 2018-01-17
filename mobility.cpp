//
// Created by A on 10/10/17.
//

#include "mobility.h"
#include <stddef.h>

Mobility::Mobility()
{
    Position = NULL;
}

Mobility::~Mobility()
{
    delete Position;
}

void Mobility::SetPosition (Coordinates *position)
{
    if (position == NULL)
    {
        Position = NULL;
        return;
    }

    if (Position == NULL)
    {
        Position = new Coordinates ();
    }

    Position->SetCoordinateX (position->GetCoordinateX ());
    Position->SetCoordinateY (position->GetCoordinateY ());
}

Coordinates* Mobility::GetPosition (void) const
{
    return Position;
}

void Mobility::DeletePosition (void)
{
    delete  Position;
}

void Mobility::SetSpeed (int speed)
{
    m_speed = speed;
}

int Mobility::GetSpeed (void) const
{
    return m_speed;
}

void Mobility::SetSpeedDirection (double speedDirection)
{
    m_speedDirection = speedDirection;
}

double
Mobility::GetSpeedDirection (void) const
{
    return m_speedDirection;
}

void Mobility::SetPositionLastUpdate (double time)
{
    m_positionLastUpdate = time;
}

double Mobility::GetPositionLastUpdate (void) const
{
    return m_positionLastUpdate;
}
