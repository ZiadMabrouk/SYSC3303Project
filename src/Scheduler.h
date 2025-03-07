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
#include "Datagram.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>        // For standard input-output
#include <vector>          // For std::vector (used to store packet data)
#include <stdexcept>       // For handling exceptions
#include <sys/time.h>      // For setting socket timeout
#include <sys/select.h>    // For using select() to monitor multiple clients
#include <unistd.h>        // For close()
#define SERVER_PORT 5000

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
    State* currentState;
    DatagramSocket sendSocket;
    DatagramSocket receiveSocket;
    fd_set readfds;
    struct timeval timeout;


public:
    Scheduler();	// Constructor

    void handle();

    void operator()();


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
