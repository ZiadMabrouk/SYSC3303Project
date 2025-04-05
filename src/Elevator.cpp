#include "Elevator.h"
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>

//TODO:  opens and closes doors time value needs to be changed to simulate live data from excel sheet.


//gets current floor
short int Elevator::getCurrentFloor() {
    return current_floor;
}

void Elevator::setCurrentFloor(short int floor) {
    current_floor = floor;
}

void Elevator::setDirection(Direction set2) {
    direction = set2;
}

//Delete if unused.
Direction Elevator::getDirection() {
    return direction;
}

// returns reference and not a copy of myQueue. if this fails then go the setter function route.
std::vector<e_struct> &Elevator::getQueue() {
    return myQueue;
}



// AS OF NOW this only to be called by .addtoQueue Method so make sure to set to this private later
// calculates direction issue with this, is that it needs the floo
void ElevatorSubsystem::calcdirection(short int pfloor) {
    if (myElevator.getCurrentFloor() < pfloor) // need to get elevators current floor.
        myElevator.setDirection(UP); // need to be able set elevators directon via ElevatorSubsytsem

    else if (myElevator.getCurrentFloor() > pfloor){
        myElevator.setDirection(DOWN);
    }
    // don't account for the case where they are equal, because when travel is called this will get auto detected and accounted for.
    //std::cerr << "Did not pass in floor number, or at least not one that exists in this building!Try again" << std::endl;
}

// TODO: Test to see if get by refenrence works as expected.
//Im gonna assume that a floor lower than the elevators current floor, when
void ElevatorSubsystem::addToQueue(e_struct request) {
    std::unique_lock<std::mutex> lock(mtx);
    // if (myElevator.getQueue().empty()) {// adds floor number, to queue.
    //     std::cout << " adding floor " << floor << std::endl;
    //     calcdirection(floor); // sets the direction
    //     myElevator.getQueue().push_back(floor); // edge cases
    // }
    // else if (myElevator.getDirection() == UP) //this part sorts the vector ascending order(up direction).
    // {
    //     myElevator.getQueue().push_back(floor);
    //     std::sort(myElevator.getQueue().begin(), myElevator.getQueue().end());
    //
    // }
    // else if (myElevator.getDirection() == DOWN)//this part sorts the vector in descending order(down direction).
    // {
    //     myElevator.getQueue().push_back(floor);
    //     std::sort(myElevator.getQueue().begin(), myElevator.getQueue().end(), std::greater<short int>());  // Descending order
    //
    // }
    myElevator.myQueue.push_back(request);
    cv.notify_all();  // Notify waiting thread

}


/**
void Elevator::travel() {
    std::unique_lock<std::mutex> lock(mtx);
    while (myQueue.empty()) cv.wait(lock);
    // this has to be called over and over again, until myQueue is empty. When I implement this functionality, somewhere it will always have to be running.
    while (myQueue.front() != current_floor) {
        std::this_thread::sleep_for(std::chrono::seconds(3));//change this to match excel
        current_floor += 1; // increments the floor by 1. (later worry about hard limit)
        std::cout << "Just passed, floor: " << current_floor << std::endl;

    }// this should also work in the case for calc direction. Do unit testing later.
    std::cout << " Arrived at target floor: " << current_floor << " Opening doors..." << std::endl;
    current_floor = myQueue.front(); //sets the current floor before deleting.
    myQueue.erase(myQueue.begin()); // only erase once you arrive at the floor. Isolate this garbage from the rest so make an doors() method. and call that
    //could have iterator function change the direction state to idle, give myQueue is empty.
    if (myQueue.empty()) {
        std::cout << "Elevator Queue is empty, direction is now IDLE" << std::endl;
        direction = IDLE;
        return;
    }
    cv.notify_all();  // Notify waiting thread

}
**/

// prints queue
void Elevator::printQueue() {
    for (auto request: myQueue) {
        std::cout << request.floorNumber << " " << request.destinationFloorNumber << " ";
    }
    std::cout << std::endl;
}

// method so that I can print the direction now that it's enum.
std::string Elevator::stringDirection(Direction direction) {
    switch (direction) {
        case UP: return "UP";
        case DOWN: return "DOWN";
        case IDLE: return "IDLE";
        default: return "UNKNOWN";
    }
}

void ElevatorSubsystem::receiverThread() {
    while (true) {
        // TODO: Consider changing Elevator to ElevatorSubystem if needed.
        received_e_struct_ = wait_and_receive_with_ack("Elevator", receiveSocket, sendSocket);

        addToQueue(received_e_struct_);

        if (received_e_struct_.fault == TIMER) {
            e_struct terminationStruct;
            terminationStruct.elevatorID = programID;
            terminationStruct.requestType = ELEVATOR;
            terminationStruct.fault = TIMER;
            send_and_wait_for_ack(threadName, terminationStruct,PORT, receiveSocket, sendSocket);
            break;
        }

        std::cout << "Elevator " << programID << "'s current direction is " << myElevator.stringDirection(myElevator.getDirection()) << std::endl;
    }
}



// make sure to pass the now Elevator Substystem programID as elevatorID
Elevator::Elevator(int elevatorID) : arrived(false), current_floor(1), direction(IDLE) , ID(elevatorID), sourceFloor(0), destinationFloor(0) {
} // initializes the elevator class to object.

//TODO: Define the constructor for ElevatorSubsystem.
// may not need programID member.
ElevatorSubsystem::ElevatorSubsystem(int elevatorID) : myElevator(elevatorID) , programID(elevatorID),currentState(new eWaitingForInput), sendSocket(), receiveSocket(PORT+elevatorID){}


void ElevatorSubsystem::operator()() {
    std::thread t1(&ElevatorSubsystem::receiverThread, this);
    handle(); // check that this works as expected.
    t1.join();
}

void ElevatorSubsystem::handle() {
    currentState->handle(this);
}

void eWaitingForInput::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Waiting for input / IDLE. Opening Doors" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Elevator " << context->programID << ": Doors Open" << std::endl;
    if (true) { // lock scope
        std::unique_lock<std::mutex> lock(context->mtx);
        while (context->myElevator.getQueue().empty()) context->cv.wait(lock);
        context->myElevator.printQueue();
        context->myElevator.sourceFloor = context->myElevator.getQueue().front().floorNumber;
        context->myElevator.destinationFloor = context->myElevator.getQueue().front().destinationFloorNumber;
    }
    std::cout << "Elevator " << context->programID << ": Received Request" << std::endl;
    context->setState(new ProcessRequest());
    context->handle();
}

void ProcessRequest::handle(ElevatorSubsystem* context) {
    if (!context->stateTest) {
        std::cout << "Elevator " << context->programID << ": Processed Request" << std::endl;
        context->setState(new CruiseAndWait());
        context->handle();
    }
}
//DOUBLE CHECK FLOOR_TO_GO_TO

void CruiseAndWait::handle(ElevatorSubsystem* context) {
    //Review the context swith changes.
    std::cout << "Moving..." << std::endl;
    while (context->myElevator.sourceFloor != context->myElevator.getCurrentFloor()) {
        std::this_thread::sleep_for(std::chrono::seconds(ELEVATOR_TIME));//change this to match excel
        if (true) { //lock scope
            std::unique_lock<std::mutex> lock(context->mtx);
            if (context->myElevator.sourceFloor > context->myElevator.getCurrentFloor()) {// Check that this works properly. increments the floor by 1. (later worry about hard limit)
                context->myElevator.setCurrentFloor(context->myElevator.getCurrentFloor() + 1);
                context->myElevator.setDirection(UP);
            } else {
                context->myElevator.setCurrentFloor(context->myElevator.getCurrentFloor() - 1);
                context->myElevator.setDirection(DOWN);
            }// increments the floor by 1. (later worry about hard limit)
            std::cout << "Current Direction: " << context->myElevator.stringDirection(context->myElevator.getDirection()) << std::endl;
        }
        context->send_e_struct_.elevatorID = context->programID;
        context->send_e_struct_.transmittedFloor = context->myElevator.getCurrentFloor();
        context->send_e_struct_.direction = context->myElevator.getDirection();
        send_and_wait_for_ack(context->threadName, context->send_e_struct_,PORT, context->receiveSocket, context->sendSocket);

        std::cout <<  "Elevator " << context->programID <<": Just passed, floor " << context->myElevator.getCurrentFloor() << std::endl;
    }
    std::cout << "Elevator " << context->programID << ": Stopped." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Moving..." << std::endl;
    while (context->myElevator.destinationFloor != context->myElevator.getCurrentFloor()) {
        std::this_thread::sleep_for(std::chrono::seconds(ELEVATOR_TIME));//change this to match excel
        if (true) { //lock scope
            std::unique_lock<std::mutex> lock(context->mtx);
            if (context->myElevator.destinationFloor > context->myElevator.getCurrentFloor()) {// Check that this works properly. increments the floor by 1. (later worry about hard limit)
                context->myElevator.setCurrentFloor(context->myElevator.getCurrentFloor() + 1);
                context->myElevator.setDirection(UP);
            } else {
                context->myElevator.setCurrentFloor(context->myElevator.getCurrentFloor() - 1);
                context->myElevator.setDirection(DOWN);
            }// increments the floor by 1. (later worry about hard limit)
            std::cout << "Current Direction: " << context->myElevator.stringDirection(context->myElevator.getDirection()) << std::endl;
        }
        context->send_e_struct_.elevatorID = context->programID;
        context->send_e_struct_.transmittedFloor = context->myElevator.getCurrentFloor();
        context->send_e_struct_.direction = context->myElevator.getDirection();
        send_and_wait_for_ack(context->threadName, context->send_e_struct_,PORT, context->receiveSocket, context->sendSocket);

        std::cout <<  "Elevator " << context->programID <<": Just passed, floor " << context->myElevator.getCurrentFloor() << std::endl;
    }
    std::cout << "Elevator " << context->programID << ": Stopped." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (context->myElevator.getQueue().front().fault == DOOR_STUCK) {
        context->setState(new JammedState());
    } else if (context->myElevator.getQueue().front().fault == TIMER) {
        context->setState(new BrokenState());
    } else {
        context->setState(new DoorsOpened());
    }
    context->handle();
}

void Stopped::handle(ElevatorSubsystem* context) {

}

void DoorsOpened::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Doors Opened." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    context->setState(new InformSchedulerOfArrival());
    context->handle();
}

void InformSchedulerOfArrival::handle(ElevatorSubsystem* context) {
    std::cout << "Informing Scheduler of Arrival" << std::endl;


    if (true) {
        std::unique_lock<std::mutex> lock(context->mtx);
        context->myElevator.getQueue().erase(context->myElevator.getQueue().begin()); // only erase once you arrive at the floor. Isolate this garbage from the rest so make an doors() method. and call that
    }

    if (context->myElevator.getQueue().empty()) {
        std::cout << "Elevator Queue is empty, direction is now IDLE" << std::endl;
        context->myElevator.setDirection(IDLE);
    }

    context->setState(new DoorsClosed());
    context->handle();
}

void DoorsClosed::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Doors Closed." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    context->setState(new eWaitingForInput());
    context->handle();
}

void BrokenState::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Stuck Between Floors." << std::endl; // <--- START HERE FOR NEXT ITERATION
}

void JammedState::handle(ElevatorSubsystem* context) {
    std::cout << "Doors Jammed.... Initiated Fixed Doors Routine." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Doors have been fixed!!" << std::endl;
    context->setState(new DoorsOpened());
    context->handle();
}

//
#ifndef UNIT_TEST
int main(int argc, char* argv[]) {
    ElevatorSubsystem elevator_subsystem(std::atoi(argv[1]));
    elevator_subsystem.operator()();
}
#endif


