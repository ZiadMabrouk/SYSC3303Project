
#include "Elevator.h"
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>

#define ELEVATOR_ID 0
#define NOT_ARRIVED 0
#define ARRIVED_FOR_PICKUP 1
#define ARRIVED_FOR_DROPOFF 2
Elevator::Elevator(Scheduler& object) : scheduler_object(object),  current_floor(0) {} // initializes the elevator class to object.

    void Elevator::operator()() { // defines how the Elevator object acts when called
        while (true) { // infinite loop
            elevator_data = scheduler_object.get();

            std::cout <<"Grab request " << "Floor Number:" << elevator_data.floor_number << std::endl;
            current_floor = elevator_data.floor_number;

            elevator_data.arrived = ARRIVED_FOR_PICKUP;
            std::cout << "Elevator has arrived at Floor Number:" << current_floor << " and the doors are open, waiting for button request"<< std::endl;
            scheduler_object.put(elevator_data, ELEVATOR_ID); // put elevator_data back into the scheduler object. to update the scheduler on elevators arrival.

            std::cout << "Elevator is now travelling to: " << elevator_data.car_to_floor_number << std::endl;
            current_floor = elevator_data.car_to_floor_number;
            elevator_data.arrived = ARRIVED_FOR_DROPOFF;
            std::cout << "Elevator has arrived at Floor Number:" << current_floor << " for drop off and the doors are now closed "<< std::endl;
            scheduler_object.put(elevator_data, ELEVATOR_ID); //

        }
    }
//gets current floor
short int Elevator::getCurrentFloor() {
    return current_floor;
}
//sets current floor
void Elevator::setCurrentFloor(short int floor) {
    current_floor = floor;
}