#include <iostream>
#include "Elevator.h"
#include "Floor.h"
#include "Scheduler.h"




int main() {
    Scheduler scheduler;
    Elevator  elevator(scheduler);

    Floor floor(scheduler);

    std::thread floor_thread( floor);

    std::thread elevatorthread(elevator);
    std::thread schedulerthread(scheduler);//


    floor_thread.join();
    elevatorthread.join();
    schedulerthread.join();

    
    return 0;
}
