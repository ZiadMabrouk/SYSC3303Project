//
// Created by ziadm on 2025-01-30.
//

#include "Scheduler.h"


Scheduler::Scheduler() : sendSocket(), receiveSocket(SERVER_PORT), currentState(new WaitingForInput()) {

}

void Scheduler::handle() {
    currentState->handle(this);
}



void Calculation::handle(Scheduler *context) {
    std::cout<<"Calculating..."<<std::endl;
    std::cout<<"Calculated"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}

void WaitingForInput::handle(Scheduler *context) {


    std::cout<<"Waiting for input... "<<std::endl;
    //logic



    std::cout<<"Input received... "<<std::endl;
    context->setState(new Dispatching());
    context->handle();

    delete this;
}

void Dispatching::handle(Scheduler *context) {
    std::cout<<"Dispatching"<<std::endl;
    //logic
    std::cout<<"Dispatched"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}

void AddingRequestToQueue::handle(Scheduler *context) {
    std::cout<<"Adding request to queue..."<<std::endl;
    std::cout<<"Added to queue"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}





void Scheduler::operator()() {
    handle();
}



