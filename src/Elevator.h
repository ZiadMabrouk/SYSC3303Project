//
// Created by ziadm on 2025-01-30.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Scheduler.h"
#include "ElevatorDataTypes.h"
#include "Datagram2.h"



class Elevator
{
private:
    e_struct elevator_data;
    Scheduler& scheduler_object;
    short int current_floor;
    // added a vector of short int
    std::vector<short int> myQueue;
    // direction
    std::string direction;
    // add in new struct to pass to daniel? potentially

    void calcdirection(short int floor); // for now only used by addtoQueue.

    void travel(); // controls
public:
    Elevator(Scheduler& object);


    void operator()();

    short int getCurrentFloor(); // simply gets current floor of the elevator instance

    void addtoQueue(short int floor); // logic for elevators path.

    void printQueue(); // should print the current queue.

    void doors(); // time taken for an elevator to both open and close its doors.

    DatagramPacket sendSocket(); //

    DatagramPacket receiveSocket(); //

};



#endif //ELEVATOR_H
