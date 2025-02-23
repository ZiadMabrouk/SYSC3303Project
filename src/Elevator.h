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
    short int current_floor;
public:
    Elevator(Scheduler& object);


    void operator()();

    short int getCurrentFloor(); // simply gets current floor of the elevator instance

    void setCurrentFloor(short int floor); // sets current floor of the elevator instance
};


#endif //ELEVATOR_H
