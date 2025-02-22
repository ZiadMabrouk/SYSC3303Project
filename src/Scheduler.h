//
// Created by ziadm on 2025-01-30.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include "ElevatorDataTypes.h"
#include "ElevatorSubsystem.h"
#include <mutex>

class Scheduler
{
private:
    bool empty = true;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
    // Added in by Sam
    ElevatorSubsystem::ElevatorSubsystem& elevator_subsystem;
    // need to keep track of requests

public:
    Scheduler();	// Constructor

    //floor calls this on the scheduler object
    void put(e_struct elevatorData);

    // Sam's method:
    // need a method which process the e_struct from floor into the request queue
    // void addFloorRequest(int floor, int direction)
    // will take in e_struct members as parameters

    //method
    // choose out of the available cars which to assign to what floor request.
    int selectElevatorCarCmd(int requestFloor);



    e_struct get();

    void operator()();
    
};


#endif //SCHEDULER_H
