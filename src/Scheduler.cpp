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




Scheduler::Scheduler() : empty(true), mtx(), cv(), currentState(new WaitingForInput()) {}

void Scheduler::put(e_struct elevatorData, int id) {


    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.

    box.push_back(elevatorData);


    if (elevatorData.floor_up_button) {
        upRequests.push_back(elevatorData.floor_number);
    }

    if (elevatorData.floor_down_button) {
        downRequests.push_back(elevatorData.floor_number);
    }

    if (id == 0) {
        std::cout<<"input received from floor"<<std::endl;

        if (elevatorOccupied) {

            setState(new AddingRequestToQueue());

        }


        else {
            setState(new Dispatching());
        }


    }

    else {
        std::cout<<"input received from floor"<<std::endl;
        setState(new Calculation());
    }

    empty = false;

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


int main(void) {

    Scheduler scheduler;
// Test struct 1
    ElevatorData test1;
    test1.datetime = {30, 14, 1, 0, 125}; // 2025-01-01 14:30:00
    test1.floor_number = 1;
    test1.floor_up_button = true;
    test1.floor_down_button = false;

    // Test struct 2
    ElevatorData test2;
    test2.datetime = {45, 16, 1, 1, 125}; // 2025-02-01 16:45:00.500
    test2.floor_number = 5;
    test2.floor_up_button = false;
    test2.floor_down_button = true;

    // Test struct 3
    ElevatorData test3;
    test3.datetime = {15, 9, 1, 2, 125}; // 2025-03-01 09:15:00.750
    test3.floor_number = 10;
    test3.floor_up_button = true;
    test3.floor_down_button = false;

    scheduler.put(test1, 0);
    scheduler.put(test2, 0);
    scheduler.put(test3, 0);

    e_struct outtest1 = scheduler.get();
    e_struct outtest2 =scheduler.get();
    e_struct outtest3 = scheduler.get();
    std::cout << "Success"; 
    return 1;
}

