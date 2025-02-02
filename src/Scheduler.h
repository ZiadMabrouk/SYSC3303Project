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

class Scheduler
{
private:
    bool empty = true;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
public:
    Scheduler();	// Constructor

    void put(e_struct elevatorData);

    void get();
};


#endif //SCHEDULER_H
