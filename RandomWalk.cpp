//
// Created by A on 10/10/17.
//

#include "RandomWalk.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define PI (3.141592653589793)
#include <iostream>


RandomWalk::RandomWalk()
{
    SetSpeed (0);
    SetSpeedDirection (0.0);
    SetPositionLastUpdate (0.0);

    SetPosition (NULL);
    m_interval = 0.;
    m_lastTimeDirectionChange = 0.;
};

RandomWalk::~RandomWalk()
{
    DeletePosition();
}


void RandomWalk::UpdatePosition(double time)
{
    double timeInterval = time - GetPositionLastUpdate(); // s //h
    double shift = timeInterval * (GetSpeed()*(1000.0/3600.0)); //metri

    double shift_y = shift * sin (GetSpeedDirection());
    double shift_x = shift * cos (GetSpeedDirection());

    Coordinates *newPosition = new Coordinates(GetPosition()->GetCoordinateX()+shift_x,
                                               GetPosition()->GetCoordinateY()+shift_y);


//    std::cout << "updata " << std::endl;
/*   std::cout << "\n\t Final Position (X): " << newPosition->GetCoordinateX()
    << "\n\t Final Position (Y): " << newPosition->GetCoordinateY()
    << std::endl;
    std::cout << "shift " << shift << " shift_x " << shift_x << " shift_y " << shift_y << " GetSpeedDirection " << GetSpeedDirection() << " GetSpeed " << GetSpeed() << std::endl;
*/


    double Border = 1000.0;//10.0;//10000.0; // km
    //when the user goes outside the Border, it is moved inside again
    do{
        if(newPosition->GetCoordinateY() > Border && newPosition->GetCoordinateX() > 0 && newPosition->GetCoordinateX() < Border && shift_x > 0 && shift_y > 0){
            SetSpeedDirection(PI + GetSpeedDirection());//+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 1 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if(newPosition->GetCoordinateY() > Border && newPosition->GetCoordinateX() > 0 && newPosition->GetCoordinateX() < Border && shift_x < 0 && shift_y > 0){
            SetSpeedDirection(PI + GetSpeedDirection()); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 2 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if(newPosition->GetCoordinateY() <0  && newPosition->GetCoordinateX() > 0 && newPosition->GetCoordinateX() < Border && shift_x > 0 && shift_y < 0){
            SetSpeedDirection(GetSpeedDirection() - PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 3 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if(newPosition->GetCoordinateY() < 0  && newPosition->GetCoordinateX() > 0 && newPosition->GetCoordinateX() < Border && shift_x < 0 && shift_y < 0){
            SetSpeedDirection(GetSpeedDirection() - PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 4 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if((newPosition->GetCoordinateX() < 0  && newPosition->GetCoordinateY() > 0 && newPosition->GetCoordinateY() < Border && shift_x < 0 && shift_y < 0)){
            SetSpeedDirection(GetSpeedDirection() - PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 5 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if((newPosition->GetCoordinateX() < 0 && newPosition->GetCoordinateY() > 0 && newPosition->GetCoordinateY() < Border && shift_x < 0 && shift_y > 0)){
            SetSpeedDirection(GetSpeedDirection() + PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 6 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if(newPosition->GetCoordinateX() > Border && newPosition->GetCoordinateY() > 0 && newPosition->GetCoordinateY() < Border && shift_x > 0 && shift_y < 0){
            SetSpeedDirection(GetSpeedDirection() - PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 6.2 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if(newPosition->GetCoordinateX() > Border && newPosition->GetCoordinateY() > 0 && newPosition->GetCoordinateY() < Border && shift_x > 0 && shift_y > 0){
            SetSpeedDirection(GetSpeedDirection() + PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 6.3 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /* std::cout << "x, y : " << newPosition->GetCoordinateX()
             << " " <<newPosition->GetCoordinateY()
             << std::endl;*/
        }
        if((newPosition->GetCoordinateX() < 0  && newPosition->GetCoordinateY() > Border) || (newPosition->GetCoordinateX() > Border && newPosition->GetCoordinateY() > Border) || (newPosition->GetCoordinateX() > Border && newPosition->GetCoordinateY() < 0)){
            SetSpeedDirection(GetSpeedDirection() + PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 7 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        else if((newPosition->GetCoordinateX() < 0  && newPosition->GetCoordinateY() < 0)){
            SetSpeedDirection(GetSpeedDirection() - PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 8 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }

        if((newPosition->GetCoordinateX() > Border && newPosition->GetCoordinateY() > 0 && newPosition->GetCoordinateY() < Border && shift_x > 0 && shift_y == 0)){
            SetSpeedDirection(PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 10 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if((newPosition->GetCoordinateX() < 0 && newPosition->GetCoordinateY() > 0 && newPosition->GetCoordinateY() < Border && shift_x < 0 && shift_y == 0)){
            SetSpeedDirection(0); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 11 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if((newPosition->GetCoordinateY() > Border && newPosition->GetCoordinateX() > 0 && newPosition->GetCoordinateX() < Border && shift_x == 0 && shift_y > 0)){
            SetSpeedDirection(GetSpeedDirection() + PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            //std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 11 " << std::endl;

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
        if((newPosition->GetCoordinateY() < 0 && newPosition->GetCoordinateX() > 0 && newPosition->GetCoordinateX() < Border && shift_x == 0 && shift_y < 0)){
            SetSpeedDirection(GetSpeedDirection() - PI); //+ GetSpeedDirection());

            double shift_y2 = shift * sin (GetSpeedDirection());
            double shift_x2 = shift * cos (GetSpeedDirection());
            /*std::cout << "shift " << shift << " shift_x " << shift_x2 << " shift_y " << shift_y2 << " GetSpeedDirection " << GetSpeedDirection() << " caso 11 " << std::endl;*/

            newPosition->SetCoordinates(newPosition->GetCoordinateX() + shift_x2,
                                        newPosition->GetCoordinateY() + shift_y2);

            /*std::cout << "x, y : " << newPosition->GetCoordinateX()
            << " " <<newPosition->GetCoordinateY()
            << std::endl;*/
        }
    }while(newPosition->GetCoordinateX() < 0 || newPosition->GetCoordinateX() > Border || newPosition->GetCoordinateY() < 0 || newPosition->GetCoordinateY() > Border);




    SetPosition(newPosition);
    SetPositionLastUpdate (time);
    delete newPosition;

//    std::cout << "x, y : " << GetPosition()->GetCoordinateX()
//    << " " << GetPosition()->GetCoordinateY()
//    << std::endl;

    if (time - m_lastTimeDirectionChange >= m_interval)
    {
        double speedDirection = (double)(rand() %360) * ((2*PI)/360);
        SetSpeedDirection(speedDirection);

        double averageDistance;
        double a;
        double b;

        if (GetSpeed()==3)
        {
            averageDistance = 200; //m
        }
        else if (GetSpeed() == 30)
        {
            averageDistance = 400;
        }
        else if (GetSpeed()==50)
        {
            averageDistance = 600;
        }
        else if (GetSpeed()==120)
        {
            averageDistance = 1000;
        }
        else
        {
            averageDistance = 200;
        }

        a = averageDistance - 100;
        b = averageDistance + 100;

        double distance = (double) (rand() %1001); //mm
        distance = distance/1000; //m   generate random numbers between 0 and 1
        distance = a + (distance * (b-a));   //m

        m_interval = distance / (GetSpeed() * 3.6); //s
        m_lastTimeDirectionChange = time;
    }
}