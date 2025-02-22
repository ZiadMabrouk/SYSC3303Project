//
// Created by ziadm on 2025-01-30.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Scheduler.h"
#include "ElevatorDataTypes.h"

class Elevator
{
private:
    e_struct elevator_data;
    Scheduler& scheduler_object;
    // iteration two additions
    //some type of motor data type
    // elevator button could also be a short class or could have it read off the e_struct?
    short int current_floor;
public:
    Elevator(Scheduler& object);	// Constructor undefined here.


    void operator()(); // undefined

    short int getCurrentFloor(); // simply gets current floor of the elevator instance

    void setCurrentFloor(short int floor); // sets current floor of the elevator instance

};


#endif //ELEVATOR_H
