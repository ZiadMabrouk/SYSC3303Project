//
// Created by ziadm on 2025-01-30.
//

#include "Elevator.h"


#include <chrono>
#include <thread>

#include <random>
#include <mutex>
#include <condition_variable>
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>



    Elevator::Elevator(Scheduler& object) : scheduler_object(object) {}

    void Elevator::operator()() {
        int i = 0;
        while (true) {
            elevator_data = scheduler_object.get();
            std::cout <<"Grab request " << i << std::endl;
            i++;
        }
    }


