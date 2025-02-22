//
// Created by ziadm on 2025-01-30.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include "Scheduler.h"
#include "ElevatorDataTypes.h"
//changed the shit out of this file.
class Elevator
{
private:
    //e_struct elevator_data; // elevator system or maybe even scheduler should be the one to have this.
    //Scheduler& scheduler_object; scheduler take in the elevatorsubsystem instead.
    // iteration two additions
    short int id; //elevator id
    std::string direction_state;//represents what direction the elevator is moving, may consider changing this because there is three states not moving
    // may not motor member? is should also have states
    short int current_floor;
    bool closed_door; // door can only be opened or closed. or potentially in process of door opening
    std::mutex mtx; // ensures only method at a time can be applied to a specific elevator

public:
    Elevator::Elevator(int id);	// Constructor undefined here. change the definition


    void operator()(); // undefined

    int getCurrentFloor();
    std::string getDirection();
    int getID();
    void moveToFloor(int stopfloor);

    void openDoors(); // controls the opening of car

    void closeDoors(); // same thing as above but with car door closing


};


#endif //ELEVATOR_H
