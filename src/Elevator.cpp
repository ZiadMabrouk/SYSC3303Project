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


class Elevator {

private:
    e_struct elevator_data;
    Scheduler& scheduler_object;

public:
    Elevator(Scheduler& object) : scheduler_object(object) {}

    void operator()() {
        while (true) {
            elevator_data = scheduler_object.get();
            std::cout <<"Grab request";
        }
    }


};