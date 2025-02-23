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

        }


        else {
            setState(new Dispatching());
        }

        empty = false;

    }

    else {
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

