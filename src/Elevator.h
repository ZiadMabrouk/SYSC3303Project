//
// Created by ziadm on 2025-01-30.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Scheduler.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include "ElevatorDataTypes.h"

class Elevator
{
private:
    e_struct elevator_data;
    Scheduler& scheduler_object;
public:
    Elevator(Scheduler& object);	// Constructor


    void operator()();
    
};


#endif //ELEVATOR_H
