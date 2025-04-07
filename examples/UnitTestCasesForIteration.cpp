
#include <cassert>
#include <iostream>
#include <ostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "../src/ElevatorDataTypes.h"
#include "../src/Elevator.h"
#include "../src/Scheduler.h"
#include "../src/Floor.h"




void testAddToQueue() {

    Scheduler scheduler(22);
    Elevator ascendingElevator(1000);

    // Test case 1: Adding the first floor to an empty queue
    ascendingElevator.addtoQueue(7);
    assert(ascendingElevator.getQueue() == std::vector<short int>{7});
    assert(ascendingElevator.direction == UP);
    std::cout << "Test 1 passed" << std::endl;


    // Test case 2: Adding higher floors to queue in ascending order when direction is UP
    assert(ascendingElevator.direction == UP);
    ascendingElevator.addtoQueue(8);
    ascendingElevator.addtoQueue(14);
    std::vector<short int> expected_vector1 = {7, 8, 14};
    assert(ascendingElevator.getQueue() == expected_vector1);
    std::cout << "Test 2 passed" << std::endl;


    // Test case 3: Adding a lower floor to queue in ascending order when direction is UP
    assert(ascendingElevator.direction == UP);
    ascendingElevator.addtoQueue(10);
    ascendingElevator.current_floor = 11;
    assert(ascendingElevator.current_floor > 10);
    std::vector<short int> expected_vector2 = {7, 8, 10, 14};
    assert(ascendingElevator.getQueue() == expected_vector2);
    std::cout << "Test 3 passed" << std::endl;


    // Elevator reset for down direction test cases
    Elevator descendingElevator(2000);
    descendingElevator.current_floor = 17;
    descendingElevator.addtoQueue(13);
    assert(descendingElevator.current_floor > 13);
    assert(descendingElevator.direction == DOWN);


    // Test case 4: Adding lower floors in descending order when direction is DOWN
    descendingElevator.addtoQueue(4);
    descendingElevator.addtoQueue(7);
    std::vector<short int> expected_vector3 = {13, 7, 4};
    assert(descendingElevator.getQueue() == expected_vector3);
    std::cout << "Test 4 passed" << std::endl;


    // Test case 5: Adding a higher floor to a queue in descending order when direction is DOWN
    descendingElevator.addtoQueue(9);
    descendingElevator.current_floor = 6;
    assert(descendingElevator.current_floor < 9);
    std::vector<short int> expected_vector4 = {13, 9, 7, 4};
    assert(descendingElevator.getQueue() == expected_vector4);
    std::cout << "Test 5 passed" << std::endl;
}


void testSchedulerConstructor() {
    Scheduler scheduler(12);
    assert(typeid(scheduler.numElevators) == typeid(int));
    assert(scheduler.numElevators == 12);
    std::cout << "Scheduler constructor test passed!" << std::endl;
};

void testGetSendSocket() {
    Scheduler scheduler(16);
    assert(typeid(scheduler.getSendSocket()) == typeid(DatagramSocket));
    std::cout << "Socket sent successfully!" << std::endl;
}

void testGetReceiveSocket() {
    Scheduler scheduler(11);
    assert(typeid(scheduler.getReceiveSocket()) == typeid(DatagramSocket));
    std::cout << "Socket received successfully!" << std::endl;
}

void testSend_And_Wait_For_Ack() {

}

int main () {
    testAddToQueue();
    testSchedulerConstructor();
    testGetSendSocket();
    testGetReceiveSocket();

}

