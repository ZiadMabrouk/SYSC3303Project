//
// Created by ziadm on 2025-01-30.
//

#include "Elevator.h"
#include <iostream>
#include "Scheduler.h"

//Scheduler::Scheduler() : empty(true), mtx(), cv() {}


    Elevator::Elevator(Scheduler& object) : scheduler_object(object) {}

    void Elevator::operator()() {
        int i = 0;
        while (true) {
            elevator_data = scheduler_object.get();
            std::cout <<"Grab request " << i << std::endl;
            i++;
        }
    }


