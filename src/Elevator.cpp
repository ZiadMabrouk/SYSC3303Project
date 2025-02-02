//
// Created by ziadm on 2025-01-30.
//

#include "Elevator.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <random>
#include <mutex>
#include <ctime> // For datetime data type
#include <condition_variable>
#include "Scheduler.h"

//Scheduler::Scheduler() : empty(true), mtx(), cv() {}


    Elevator::Elevator(Scheduler& object) : scheduler_object(object) {}

    void Elevator::operator()() {
        while (true) {
            elevator_data = scheduler_object.get();
            std::cout <<"Grab request";
        }
    }


