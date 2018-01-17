//
// Created by A on 10/10/17.
//

#include "Coordinates.h"
#include <math.h>
#include <cmath>

Coordinates::Coordinates(){}

Coordinates::Coordinates(double x, double y){
    SetCoordinates(x,y);
}

Coordinates::~Coordinates(){
};

void Coordinates::SetCoordinates(double x, double y){
    posX = x;
    posY = y;
}

double Coordinates::GetCoordinateX()
{
    return posX;
}

double Coordinates::GetCoordinateY()
{
    return posY;
}

void Coordinates::SetCoordinateX(double X)
{
    posX = (double) X;
}

void Coordinates::SetCoordinateY(double Y)
{
    posY = (double) Y;
}



double Coordinates::GetDistance(double remoteObjectPosX, double remoteObjectPosY)
{

    return sqrt (pow ((GetCoordinateX() - remoteObjectPosX),2) + pow ((GetCoordinateY() - remoteObjectPosY),2));
}

double Coordinates::GetDistance(Coordinates *remoteObject)
{
    /*
     * Computes distance from this object and remoteObject
     */
    return
            sqrt (pow ((GetCoordinateX() - remoteObject->GetCoordinateX()),2) +
                  pow ( (GetCoordinateY() - remoteObject->GetCoordinateY()) ,2));

}


Coordinates* Coordinates::operator+(Coordinates* A)
{
    Coordinates *Result =
            new Coordinates ((GetCoordinateX() + A->GetCoordinateX()), (GetCoordinateY() + A->GetCoordinateY()));
    return Result;
}

Coordinates* Coordinates::operator-(Coordinates* B)
{
    Coordinates *Result =
            new Coordinates ((GetCoordinateX() - B->GetCoordinateX()), (GetCoordinateY() - B->GetCoordinateY()));
    return Result;
}
