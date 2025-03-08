#include "Elevator.h"
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>

#define ELEVATOR_ID 0
#define NOT_ARRIVED 0
#define ARRIVED_FOR_PICKUP 1
#define ARRIVED_FOR_DROPOFF 2
// Assuming scheduler will not send me a floor that is lower than my current floor, if I am moving in the UP direction
// Scheduler can only do the above if car direction is set to "IDLE" aka stopped.
// assume all caps will be used for direction data from scheduler.

// 1 thread or 3 lol.
// receiving data socket
// travel there
// send data to scheduler

// What I have left.
// communications
//

//gets current floor
short int Elevator::getCurrentFloor() {
    return current_floor;
}

// opens and closes doors and simulate live data from excel sheet.
void Elevator::doors() {
    std::cout << "Doors Open. " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); //change this to exact value later
    std::cout << "Doors Closed. " << std::endl;
}


// AS OF NOW this only to be called by .addtoQueue Method so make sure to set to this private later
// calculates direction issue with this, is that it needs the floo
void Elevator::calcdirection(short int pfloor) {
    if (current_floor < pfloor)
        direction = UP;

    else if (current_floor > pfloor){
        direction = DOWN;
    }
    // don't account for the case where they are equal, because when travel is called this will get auto detected and accounted for.
    //std::cerr << "Did not pass in floor number, or at least not one that exists in this building!Try again" << std::endl;
}

//Im gonna assume that a floor lower than the elevators current floor, when
void Elevator::addtoQueue(short int floor) {
    if (myQueue.empty())
    {// adds floor number, to queue.
        calcdirection(floor); // sets the direction
        myQueue.push_back(floor); // edge cases
    }
    else if (direction == UP) //this part sorts the vector ascending order(up direction).
    {
        myQueue.push_back(floor);
        std::sort(myQueue.begin(), myQueue.end());
    }
    else if (direction == DOWN)//this part sorts the vector in descending order(down direction).
    {
        myQueue.push_back(floor);
        std::sort(myQueue.begin(), myQueue.end(), std::greater<short int>());  // Descending order

    }
}

// need to check if myQueue is empty at some point after a pop, so I can change its direction to IDLE
//when traveling to next element.
void Elevator::travel() {
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
}


// prints queue,
void Elevator::printQueue() {
    for (int num: myQueue) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// for now have a method


Elevator::Elevator(Scheduler& object) : scheduler_object(object),  current_floor(0), direction("IDLE") {} // initializes the elevator class to object.

    void Elevator::operator()() { // defines how the Elevator object acts when called
        int i = 1;
        while (i) { // infinite loop
            // elevator_data = scheduler_object.get();
            //
            // std::cout <<"Grab request " << "Floor Number:" << elevator_data.floor_number << std::endl;
            // current_floor = elevator_data.floor_number;
            //
            // elevator_data.arrived = ARRIVED_FOR_PICKUP;
            // std::cout << "Elevator has arrived at Floor Number:" << current_floor << " and the doors are open, waiting for button request"<< std::endl;
            // scheduler_object.put(elevator_data, ELEVATOR_ID); // put elevator_data back into the scheduler object. to update the scheduler on elevators arrival.
            //
            // std::cout << "Elevator is now travelling to: " << elevator_data.car_to_floor_number << std::endl;
            // current_floor = elevator_data.car_to_floor_number;
            // elevator_data.arrived = ARRIVED_FOR_DROPOFF;
            // std::cout << "Elevator has arrived at Floor Number:" << current_floor << " for drop off and the doors are now closed "<< std::endl;
            // scheduler_object.put(elevator_data, ELEVATOR_ID);

            this->addtoQueue(3);
            std::cout << "elevators current direction is " << direction << std::endl; //TODO: Change Direction to a string before passing it into a print
            travel();
            this->printQueue();
            this->addtoQueue(1);
            this->addtoQueue(16);
            this->addtoQueue(2);
            this->printQueue();
            travel();
            i--;
        }
    }
