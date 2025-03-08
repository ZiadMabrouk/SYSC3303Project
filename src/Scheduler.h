//
// Created by ziadm on 2025-01-30.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include "ElevatorDataTypes.h"

class Scheduler;
class State {
public:
    virtual void handle(Scheduler* context) = 0;
    virtual ~State() = default;

};
// Concrete state: WaitingForInput
class WaitingForInput : public State {
public:
    void handle(Scheduler* context) override;
};

// Concrete state: Dispatching
class Dispatching : public State {
public:
    void handle(Scheduler* context) override;
};

// Concrete state: AddingRequestToQueue
class AddingRequestToQueue : public State {
public:
    void handle(Scheduler* context) override;
};

// Concrete state: Calculation
class Calculation : public State {
public:
    void handle(Scheduler* context) override;
};



class Scheduler
{
private:
    bool empty = true;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
    State* currentState = new WaitingForInput();
    std::vector<short int> upRequests;
    std::vector<short int> downRequests;
    std::vector<e_struct> box;
    std::vector<e_struct> elevators;
    int numElevators;

public:
    bool elevatorOccupied = false;
    bool floorProduced = false;
    bool elevatorProduced = false;
    bool requestInList = false;
    e_struct sendData;
    e_struct receiveData;
    Scheduler();	// Constructor
    Scheduler(int num_elevators);

    void put(e_struct elevatorData, int id);

    e_struct get();

    void operator()();

    int calculateScore(e_struct& elevator, int requestedFloor, Direction direction);

    int calculateBestScore(int requestedFloor, Direction requestedDirection);

    void setState(State* state) {
        currentState = state;
    }

    void request() {
        currentState->handle(this);
    }

    ~Scheduler() {
        delete currentState;
    }
};


#endif //SCHEDULER_H
