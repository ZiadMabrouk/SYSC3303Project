//
// Created by ziadm on 2025-01-30.
//
#include <chrono>
#include <thread>
#include <iostream>
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

void Calculation::handle(Scheduler *context) {
    std::cout<<"Calculating..."<<std::endl;
    std::cout<<"Calculated"<<std::endl;
    context->setState(new WaitingForInput());
    delete this;
}

void WaitingForInput::handle(Scheduler *context) {

    while (1) {
        std::cout<<"Waiting for input... "<<std::endl;
        //logic
        if (context->requestInList && context->elevatorProduced == false) {
            std::cout<<"Servicing request in Queue"<<std::endl;
            context->setState(new Dispatching());
            break;
        }

    }
    delete this;
}

void Dispatching::handle(Scheduler *context) {
    std::cout<<"Dispatching"<<std::endl;
    //logic
    std::cout<<"Dispatched"<<std::endl;
    context->setState(new WaitingForInput());
    delete this;
}

void AddingRequestToQueue::handle(Scheduler *context) {
    std::cout<<"Adding request to queue..."<<std::endl;
    std::cout<<"Added to queue"<<std::endl;
    context->setState(new WaitingForInput());
    delete this;
}




Scheduler::Scheduler(int num_elevators) : empty(true), mtx(), cv(), currentState(new WaitingForInput()), numElevators(num_elevators) {

    elevators.resize(numElevators);
    for (int i = 0; i < numElevators; i++) {
        elevators[i].elevatorNumber = i;
        elevators[i].currentFloor = 1;
        elevators[i].direction = IDLE;
    }
}

Scheduler::Scheduler() : empty(true), mtx(), cv(), currentState(new WaitingForInput()) {
    numElevators = 3;
    elevators.resize(numElevators);
    for (int i = 0; i < numElevators; i++) {
        elevators[i].elevatorNumber = i;
        elevators[i].currentFloor = 1;
        elevators[i].direction = IDLE;
    }
}

void Scheduler::put(e_struct elevatorData, int id) {

    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.

    if (elevatorData.floor_up_button) {
        upRequests.push_back(elevatorData.floor_number);
    }

    if (elevatorData.floor_down_button) {
        downRequests.push_back(elevatorData.floor_number);
    }

    if (id == 1) {
        std::cout<<"input received from floor"<<std::endl;
        box.push_back(elevatorData);
        if (elevatorOccupied) {
            setState(new AddingRequestToQueue());
        } else {
            setState(new Dispatching());
        }
        empty = false;
    } else {
        std::cout<<"input received from elevator"<<std::endl;
        setState(new Calculation());//
    }


    cv.notify_all();
}

e_struct Scheduler::get() {
    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    while ( empty ) cv.wait(lock);

    e_struct data = box.front();
    box.erase(box.begin());
    if (box.empty()) {
        empty = true;
    }
    cv.notify_all();
    return data;
}
void Scheduler::operator()() {
    Scheduler* scheduler = new Scheduler();
    while (1) {
        scheduler->request();

    }
    delete scheduler;
}

int Scheduler::calculateScore(elevatorMessage& elevator, int requestedFloor, Direction requestedDirection) {
    // Base score is absolute distance.
    int score = std::abs(elevator.currentFloor - requestedFloor);

    // If elevator is idle, that's the whole score.
    if (elevator.direction == IDLE) {
        return score;
    }

    // If elevator is already heading in the right direction and will pass the requested floor, increase the score.
    if ((elevator.direction == UP && requestedFloor > elevator.currentFloor && requestedDirection == UP) || (elevator.direction == DOWN && requestedFloor < elevator.currentFloor && requestedDirection == DOWN)) {
        return score * 2;
    }

    // Otherwise the elevator is moving away from the requested floor, or it's moving in the wrong direction
    return score / 2;
}

// Determines the elevator with the best(biggest) score and returns its index.
int Scheduler::calculateBestScore(int requestedFloor, Direction requestedDirection) {

    int bestElevatorIndex = 0;
    int bestScore = calculateScore(elevators[0], requestedFloor, requestedDirection);

    for (int i = 1; i < numElevators; i++) {
        int score = calculateScore(elevators[i], requestedFloor, requestedDirection);
        if (score > bestScore) {
            bestScore = score;
            bestElevatorIndex = i;
        }
    }

    return bestElevatorIndex;
}