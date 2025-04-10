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
#include <functional>
#include <map>
#include <queue>
#include <unordered_map>

#define ELEVATOR_TIME 3
#define DOORS_TIME 1
class ElevatorSubsystem;
class eState {
public:
    virtual void handle(ElevatorSubsystem* context) = 0;
    virtual ~eState() = default;

};

class eWaitingForInput : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};

class ProcessRequest : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};
class CruiseAndWait : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};
class Stopped : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};
class DoorsOpened : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};
class InformSchedulerOfArrival : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};
class DoorsClosed : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};
class BrokenState : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};
class JammedState : public eState {
public:
    void handle(ElevatorSubsystem* context) override;
};

class Elevator
{
private:



    //void calcdirection(short int floor); // for now only used by addtoQueue. Will need to be Removed.

public:

    //e_struct send_e_struct_;
    int arrived;
    short int current_floor;
    int floor_to_go_to;
    std::string user_direction;
    Direction direction; // direction
    //std::string threadName; // string name to be used in Ziads interface.
    //e_struct received_e_struct_;

    //std::mutex mtx; // Mutex for myQueue and threads
    //std::condition_variable cv; // Condition variable for signaling

    /**
     *{1: ["DOWN",}
     *scheduler {1: [{"DOWN", 2}, {"", 2}]}
     *floor three pressed the up button and the down button
     * floor 2 pressed the button to go down
     */
    std::map<short int, std::vector<std::pair<std::string, short int>>, std::function<bool(short int, short int)>> schedulerQueue; // added a vector of short int


    /**Key is the floor in combination with the direction
     *ex: {"2DOWN": [{1,2}]}
     *
     */

    // 1. Scheduler to elevator (Pick up request)
    // 2. User-to-elevator (drop off request)

    std::map<std::string, std::vector<std::pair<int, int>>> userQueue;
    int ID; // elevator ID
    int destinationFloor;
    //DatagramSocket sendSocket; // double check, this is a guess
    //DatagramSocket receiveSocket; // double check, this is a guess

    // modified consructor so the scheduler
    explicit Elevator(int elevatorID);

    //void operator()();



    //void addtoQueue(short int floor); // logic for elevators path.

    // can remain in elevator class.
    void printQueue(); // should print the current queue.

    // void setState(eState* state) {
    //     currentState = state;
    // }

    //modify so that this returns the elevators current direction as a string.
    std::string stringDirection(Direction direction);

    //void handle();

    //void receiverThread();

    void setCurrentFloor(short int floor);


    // can remain a part of Elevator.
    short int getCurrentFloor();

    void setDirection(Direction set2);

    Direction getDirection();

    std::map<short int, std::vector<std::pair<std::string, short int>>, std::function<bool(short int, short int)>> &getQueue();


};



// The wrapper class.
class ElevatorSubsystem {
private:



public:
    bool stateTest = false;
    eState* currentState;
    std::mutex mtx; // Mutex for myQueue and threads
    std::condition_variable cv; // Condition variable for signaling
    e_struct send_e_struct_; // for UDP communication to scheduler
    e_struct received_e_struct_; //
    //is elevators current floor something that should be saved into a var or just directly passed into send_e_struct?
    //
    short int programID;
    std::string threadName; // string name to be used in Ziads interface.
    Elevator myElevator;
    DatagramSocket sendSocket; // double check, this is a guess Remove.
    DatagramSocket receiveSocket; // double check, this is a guess Remove.
    bool doorsJammed = false;
    int capacity = 0;

    // constructor header for ElevatorSubsytem Constructor
    explicit ElevatorSubsystem(int elevatorID);

    int deleteEntry(
        std::map<short int, std::vector<std::pair<std::string, short int> >, std::function<bool(short int, short int)> >
        &
        schedulerQueue,
        int key);

    void userQueuePush(int key, int value);

    bool userQueuePop(int floor, const std::string &direction, int number_of_pops);

    void calcdirection(short int floor);

    void addtoQueue(short int floor, short int car_to_floor); // logic for elevators path.
    void sortMapInPlace(std::map<short int, std::vector<std::pair<std::string, short int>>, std::function<bool(short int, short int)>> &m,
                        bool ascending);

    void receiverThread();

    void setState(eState* state) {
        currentState = state;
    }


    void handle();

    void idleWithDoorsOpen();


    void operator()();

    std::pair<short int, std::pair<std::string, short int>> front(const std::map<short int, std::vector<std::pair<std::string, short int>>, std::function<bool(short int, short int)>> &m);
};




#endif //ELEVATOR_H
