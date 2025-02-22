#include "Elevator.h"

#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <thread>

void Elevator::operator()() {
    while (true) {
        switch (state) {
            case IDLE:
                std::cout << "Elevator is idling..." << std::endl;
                data = scheduler.get();
                state = (data.floor_number < floorNumber) ? MOVING_DOWN : MOVING_UP;
                break;
            case MOVING_DOWN:
                std::cout << "Elevator is moving down (Floor " << data.floor_number << ")." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
                floorNumber = data.floor_number;
                state = OPENING;
                break;
            case MOVING_UP:
                std::cout << "Elevator is moving up (Floor " << data.floor_number << ")." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
                floorNumber = data.floor_number;
                state = OPENING;
                break;
            case OPENING:
                std::cout << "Elevator is opening (Floor " << floorNumber << ")." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                state = OPEN;
                break;
            case OPEN:
                std::cout << "Elevator is open for 5s (Floor " << floorNumber << ")." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(5));
                state = CLOSING;
                break;
            case CLOSING:
                std::cout << "Elevator is closing (Floor " << floorNumber << ")." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                state = IDLE;
                break;
        }
    }
}

ElevatorState Elevator::getState() {
    return state;
}

void Elevator::setState(ElevatorState state) {
    this->state = state;
}
