#include <iostream>
#include "Elevator.h"
#include "Floor.h"
#include "Scheduler.h"
#include <chrono>
#include <thread>
#include <random>
#include <mutex>
#include <condition_variable>

#include "ElevatorSubsystem.h"


int main() {
    Scheduler scheduler;
    Elevator elevator(scheduler);
    Floor floor(scheduler);

    std::thread floorThread( floor, "../data/tests/SamTestCase.txt");
    std::thread elevatorThread(elevator);

    floorThread.join();
    elevatorThread.join();

    return 0;
}
