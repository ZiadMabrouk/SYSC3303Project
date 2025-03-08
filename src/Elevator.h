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

class eCalculation : public eState {
public:
    void handle(Elevator* context) override;
};
class Accelerate : public eState {
public:
    void handle(Elevator* context) override;
};
class CruiseAndWait : public eState {
public:
    void handle(Elevator* context) override;
};
class Recalculate : public eState {
public:
    void handle(Elevator* context) override;
};
class Deaccelerate : public eState {
public:
    void handle(Elevator* context) override;
};
class Stopped : public eState {
public:
    void handle(Elevator* context) override;
};
class DoorsOpening : public eState {
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
class ClosingDoors : public eState {
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
    e_struct received_e_struct_;
    e_struct send_e_struct_;
    Scheduler& scheduler_object;
    short int current_floor;
    // added a vector of short int
    std::vector<short int> myQueue;
    // direction
    Direction direction;
    // add in new struct to pass to daniel? potentially

    void calcdirection(short int floor); // for now only used by addtoQueue.

    void travel(); // controls

    // elevator ID
    int myID;

    // string name to be used in Ziads interface.
    std::string threadName;

    std::mutex mtx; // Mutex for myQueue and threads
    std::condition_variable cv;         // Condition variable for signaling



public:
    // modified consructor so the scheduler
    Elevator(Scheduler& object);


    void operator()();

    short int getCurrentFloor(); // simply gets current floor of the elevator instance

    void addtoQueue(short int floor); // logic for elevators path.

    void printQueue(); // should print the current queue.

    std::string stringDirection(Direction direction);

    void doors(); // time taken for an elevator to both open and close its doors.

    DatagramSocket sendSocket; // double check, this is a guess

    DatagramSocket receiveSocket; // double check, this is a guess

    void receiverThread();

    void mainThread();

    void senderThread();
};



#endif //ELEVATOR_H
