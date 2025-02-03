#include <iostream>
#include "Elevator.h"
#include "Floor.h"
#include "Scheduler.h"
#include <chrono>
#include <thread>
#include <random>
#include <mutex>
#include <condition_variable>

// this is jinans file to modify

int main() {
    Scheduler scheduler;
    Elevator  elevator(scheduler);

    Floor floor(scheduler);

    std::thread floor_thread( floor);
    std::thread elevatorthread(elevator);


    floor_thread.join();
    elevatorthread.join();

    
    return 0;
}
