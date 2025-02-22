#include <iostream>
#include "Elevator.h"
#include "Floor.h"
#include "Scheduler.h"
#include <chrono>
#include <thread>
#include <random>
#include <mutex>
#include <condition_variable>



int main() {
    Scheduler scheduler; // create a scheduler object
    Elevator  elevator(scheduler); // create a elevator object with reference to the scheduler object on the first line

    Floor floor(scheduler); //create a floor object with refernce to the scdueler object on the first line.

    std::thread floor_thread( floor); // creates a floor thread
    std::thread elevatorthread(elevator); // creates a elevator thread


    floor_thread.join();
    elevatorthread.join();

    
    return 0;
}
