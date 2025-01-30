//
// Created by ziadm on 2025-01-30.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include "Scheduler.h"


template <typename Type> class Elevator
{
private:
    std::string name;
    Scheduler<Type>& scheduler;

public:
    Elevator( Scheduler<Type>& a_scheduler ) : name(), scheduler(a_scheduler) {}
    void operator()( const std::string& name ) {}
};


#endif //ELEVATOR_H
