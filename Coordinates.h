//
// Created by A on 10/10/17.
//

#ifndef QUEUE_PROVA2_COORDINATES_H
#define QUEUE_PROVA2_COORDINATES_H

#include <math.h>
#include <cmath>

class Coordinates{

    double posX;
    double posY;
public:
    Coordinates();
    Coordinates(double x, double y);
    virtual ~Coordinates();
    void SetCoordinates(double x, double y);
    double GetCoordinateX();
    double GetCoordinateY();
    void SetCoordinateX(double X);
    void SetCoordinateY(double Y);
    double GetDistance(double remoteOBjPosX, double remoteOBjPosY);
    double GetDistance(Coordinates *remoteObject);
    Coordinates* operator + (Coordinates *A);
    Coordinates* operator - (Coordinates *B);
};




#endif //QUEUE_PROVA2_COORDINATES_H
