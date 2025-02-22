
//#include "Elevator.h" included in ElevatorSubsytemm
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include "ElevatorSubsystem.h"

// alright so where the fuck do I even start.
// what I am supposed to add according to document?
// First thing is Assume there is only one elevator and only for modularity
// Must notify the scheduler that an elevator has reached a floor
    // so once an elevator has been told to move, the elevator subsystem also has to be informed(how ?) so that it can send out messages back to scheduler
    // to denote the arrival by an elevator.
    // Need to maintain a single event list(see state machine for the specific events I guess)
// To summarize figure out how to:
    // 1. how the elevator subsystem as a whole knows when an elevator reaches a floor
        // could make a method or add somthing to operator?
        // need to track when the elevator arrives somewhere
        // possibly need an ElevatorSubsystem
            // One approach would be to make an elevator class which takes an ElevatorSubsytem as a parameter
            // would need to keep track of the current floor the elevator is at. somehow
        // each elevator will have its own buttons (will come from the press of the cart in the input file but elevator should not travel there right away) , and button led, and a motor(moves up or down) so add all this to the
    // 2. how does the elevator send a message send out the message back to the scheduler
        //
    // 3. the single event list implementation. could create a vector or somesort of list.
        //

//Going to change the shit out of this file.
Elevator::Elevator(int id) : id(id),current_floor(1),direction_state("IDLE"), closed_door(true) {} // initializes the elevator class to object.


void Elevator::moveToFloor(int stopfloor) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Elevator " << id << " moving from " << current_floor << " to " << stopfloor << " \n";
    current_floor = stopfloor;
    direction_state = "IDLE";
}

// elevator operation which opens car door
void Elevator::openDoors() {
    std::lock_guard<std::mutex> lock(mtx);
    closed_door = false;
    std::cout << "Elevator " << id << "'s doors opened at floor " << current_floor << "\n";
}

// elevator operation which closes car door
void Elevator::closeDoors() {
    std::lock_guard<std::mutex> lock(mtx);
    closed_door = true;
    std::cout << "Elevator " << id << "'s doors at floor " << current_floor << "are now closed" << "\n";
}

// basic getter function
int Elevator::getCurrentFloor() {
    return current_floor;
}


std::string Elevator::getDirection() {
    return direction_state;
}

int Elevator::getID() {
    return id;
}







//void Elevator::operator()() { // defines how the Elevator object acts when called
        //int i = 0; // still don't understand this at all
        ///while (true) { // infinite loop
           // elevator_data = scheduler_object.get(); // we are assigning elevator data to e_struct returned from the schdeduler object's method, which gets it from shared text
            // assuming this is scheduler input/request

            // take in elevator_data object. add pickups to one queue, and dropoff to another local queue. now is the gonna be one queue or multiple?
            // is each elevator gonna have it's own queue/quees or will there be a global queue?

            // May or not need to circumvent this with a list ? or not just get this garbage working.
            // what kind of garbage do I want to put in a list?

            // This segment just prints whats taken may
            // before the second scheduler_object.get() call say someone arrived at floor 2 and wants to go to someohter floor
            //std::cout <<"Grab request " << "Floor Number:" << elevator_data.floor_number << std::endl;
            // Now Elevator subsystem needs to trigger one of its elevators' motor to go to this floor

            // once elevator arrives at this floor print a message saying the elevator arrived at this floor and the doors have now opened
            //std::cout << "Elevator has arrived at Floor Number:" << elevator_data.floor_number << " and the doors are open, waiting for button request"<< std::endl;

            // button request is also in the file, the only issue is two people can enter a floor and want to go to different places but ignore this
            // button should be read from the input file type? (double check for now assume this is the case) need to introduce new data type.
            //std::cout << "Elevator is now travelling to: " << elevator_data.car_to_floor_num << std::endl;
            //

            // maybe prior to the increment and some sort of condtional
            //i++;//commenting this out changed nothing.
        //}
    //}

//Let's start at by making sure how the elevator knows it reaches a floor.could be at the end of the line
// so is their even floor tracking going on ? it really does not seem that way.
//

//each elevator has elevator buttons
// a set of elevator lamps which indicate which floors will be visited by the elevator( like on the buttons or the current floor shit )
// elevator motor , moves elevator between floors.
// There are elevator doors as well opens and closes the doors.


// semantics continued. would have to check