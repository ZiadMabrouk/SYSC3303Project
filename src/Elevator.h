//
// Created by ziadm on 2025-01-30.
//

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Scheduler.h"
#include "ElevatorDataTypes.h"
#include "Datagram2.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <algorithm>

class Elevator;
class eState {
public:
    virtual void handle(Elevator* context) = 0;
    virtual ~eState() = default;

};

class eWaitingForInput : public eState {
public:
    void handle(Elevator* context) override;
};

class ProcessRequest : public eState {
public:
    void handle(Elevator* context) override;
};
class CruiseAndWait : public eState {
public:
    void handle(Elevator* context) override;
};
class Stopped : public eState {
public:
    void handle(Elevator* context) override;
};
class DoorsOpened : public eState {
public:
    void handle(Elevator* context) override;
};
class InformSchedulerOfArrival : public eState {
public:
    void handle(Elevator* context) override;
};
class DoorsClosed : public eState {
public:
    void handle(Elevator* context) override;
};
class Elevator
{
private:

    eState* currentState;

    void calcdirection(short int floor); // for now only used by addtoQueue.

public:
    e_struct send_e_struct_;
    int arrived;
    short int current_floor;
    int floor_to_go_to;
    Direction direction; // direction
    std::string threadName; // string name to be used in Ziads interface.
    e_struct received_e_struct_;

    std::mutex mtx; // Mutex for myQueue and threads
    std::mutex mtx2; // Mutex for send_elevator_data and threads
    std::condition_variable cv; // Condition variable for signaling
    std::vector<short int> myQueue; // added a vector of short int
    int ID; // elevator ID
    DatagramSocket sendSocket; // double check, this is a guess
    DatagramSocket receiveSocket; // double check, this is a guess

    // modified consructor so the scheduler
    explicit Elevator(int elevatorID);

    void operator()();

    std::vector<short int> getQueue();

    void addtoQueue(short int floor); // logic for elevators path.

    void printQueue(); // should print the current queue.

    void setState(eState* state) {
        currentState = state;
    }

    std::string stringDirection(Direction direction);

    void handle();

    void receiverThread();
};



#endif //ELEVATOR_H
