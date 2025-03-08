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
    std::lock_guard<std::mutex> lock(mtx);
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
    cv.notify_all();  // Notify waiting thread

}

// need to check if myQueue is empty at some point after a pop, so I can change its direction to IDLE
//when traveling to next element.
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


// prints queue
void Elevator::printQueue() {
    for (int num: myQueue) {
        std::cout << num << " ";
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

// this thread will communicate will be receiving from scheduler.
void Elevator::receiverThread() {
    // does the name for receiving matter, when elevator is receiving can't it just be sheduler?
    // have ziad check, my sockets, becuase what I did was scuffed.
    while (true) { // may have to consider removing some of this logic into mainThread instead.
        received_e_struct_ = scheduler_object.wait_and_receive_with_ack("Scheduler", receiveSocket, sendSocket);
        // now pass it into add_queue, to update myQueue vector
        addtoQueue(received_e_struct_.transmittedFloor); // only thread to call addtoQueue is this one, but myQueue itself will change
        // as other threads exeucute

        if (ID != received_e_struct_.elevatorID) {
            ID = received_e_struct_.elevatorID; // sets the ID for the sender string name, should only do this once
            threadName = "Elevator " + std::to_string(ID); // sets the threadName for the senderThread, to be able to properly communicate
        }
        std::cout << threadName << "'s current direction is " << stringDirection(direction) << std::endl;

    }
}

void Elevator::mainThread() {
    while (true){
    // this will just have elevator move through floors until reaches it's destination.
        //travel(); // may need to modify to change e_struct elevators data?
        std::lock_guard<std::mutex> lock(mtx2);
        send_e_struct_.elevatorID = ID;
        send_e_struct_.transmittedFloor = current_floor;
        send_e_struct_.direction = direction;
        send_e_struct_.arrived = arrived;
    }
}

void Elevator::senderThread() {
    scheduler_object.send_and_wait_for_ack(threadName, send_e_struct_,PORT + ID, sendSocket, receiveSocket);
}


Elevator::Elevator(Scheduler& object, int elevatorID) : arrived(false), currentState(new eWaitingForInput), floor_to_go_to(), scheduler_object(object),  current_floor(1), direction(IDLE) , ID(elevatorID), sendSocket(), receiveSocket(PORT+elevatorID) {
} // initializes the elevator class to object.

void Elevator::operator()() { // defines how the Elevator object acts when called
    //int i = 1;
    //while (true) { // infinite loop
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

    // e_struct that will tell me what to add into my queue.
    //elevator_data = scheduler_object.wait_and_receive_with_ack("elevatorX", receiveSocket, sendSocket);

    //void return type what I am sending the scheduler so my e_struct with my shit, which will just call somet

    //elevator will have positive id and floor will be negative.

    //scheduler_object.send_and_wait_for_ack("elevatorX", elevator_data,5000, sendSocket, receiveSocket);



    //this->addtoQueue(3);
    //std::cout << "elevators current direction is " << direction << std::endl; //Change Direction to a string before passing it into a print
    //travel();
    //this->printQueue();
    //this->addtoQueue(1);
    //this->addtoQueue(16);
    //this->addtoQueue(2);
    //this->printQueue();
    //travel();
    //i--;

    std::thread t1(&Elevator::receiverThread, this);
    std::thread t2(&Elevator::mainThread, this);
    std::thread t3(&Elevator::senderThread, this);

    t1.detach();
    t2.detach();
    t3.detach();
}

std::vector<short int> Elevator::getQueue() {
    return myQueue;
}

void Elevator::handle() {
    currentState->handle(this);
}

void eWaitingForInput::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << "Waiting for input / IDLE" << std::endl;

    if (true) { // lock scope
        std::unique_lock<std::mutex> lock(context->mtx);
        while (context->myQueue.empty()) context->cv.wait(lock);
        context->floor_to_go_to = context->myQueue.front();
    }
    std::cout << "Elevator " << context->ID << "Received Request" << std::endl;
    context->setState(new ProcessRequest());
    context->handle();
}

void ProcessRequest::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << "Processed Request" << std::endl;
    context->setState(new CruiseAndWait());
    context->handle();

}

void CruiseAndWait::handle(Elevator* context) {
    std::cout << "Moving..." << std::endl;
    while (context->floor_to_go_to != context->current_floor) {
        std::this_thread::sleep_for(std::chrono::seconds(3));//change this to match excel
        context->current_floor += 1; // increments the floor by 1. (later worry about hard limit)
        std::cout << "Just passed, floor: " << context->current_floor << std::endl;

        //check if we receive a new request and need to change floor_to_go_to
        int new_state = false;
        std::unique_lock<std::mutex> lock(context->mtx);
        if (context->myQueue.front() != context->floor_to_go_to) {
            std::cout <<"New input received" << std::endl;
            context->floor_to_go_to = context->myQueue.front();
            new_state = true;
        }
        if (new_state == true) {
            context->setState(new ProcessRequest());
            context->handle();
        }

    }

    context->setState(new Stopped());
}

void Stopped::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Stopped." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    context->setState(new DoorsOpened());
    context->handle();
}

void DoorsOpened::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Doors Opened." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    context->setState(new InformSchedulerOfArrival());
    context->handle();
}

void InformSchedulerOfArrival::handle(Elevator* context) {
    std::cout << "Informing Scheduler of Arrival" << std::endl;
    if (true) {
        std::lock_guard<std::mutex> lock(context->mtx2);
        context->send_e_struct_.arrived = true;
    }
    context->setState(new DoorsClosed());
    context->handle();
}

void DoorsClosed::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Doors Closed." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (true) {
        std::lock_guard<std::mutex> lock(context->mtx2);
        context->send_e_struct_.arrived = false;
    }
    context->setState(new eWaitingForInput());
    context->handle();
}




