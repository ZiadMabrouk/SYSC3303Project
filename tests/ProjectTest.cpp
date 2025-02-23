#include <cassert>
#include <iostream>
#include <ostream>
#include <thread>

#include "../src/ElevatorDataTypes.h"
#include "../src/Elevator.h"
#include "../src/Elevator.cpp"
#include "../src/Scheduler.h"
#include "../src/Scheduler.cpp"
#include "../src/Floor.h"
#include "../src/Floor.cpp"

// Expected: setCurrentFloor() should update the current floor and getCurrentFloor() should get the floor where elevator is at currently.
void testElevatorSetGetCurrentFloor() {
    Scheduler scheduler;
    Elevator elevator(scheduler);

    // Check the initial floor.
    assert(elevator.getCurrentFloor() == 0);

    // Update the elevator's current floor and verify.
    elevator.setCurrentFloor(7);
    assert(elevator.getCurrentFloor() == 7);

    std::cout << "Elevator set/get current floor test passed." << std::endl;
}

// Given Input: 14:15:47.876, Expected Output: tm object with hours, mins and secs formatted into it.
void testFloorFormatTime() {
    Scheduler scheduler;
    Floor floor(scheduler);

    tm time = floor.formatTime("14:15:47.876");

    assert(time.tm_hour == 14);
    assert(time.tm_min == 15);
    assert(time.tm_sec == 47);
}
// Expected:
void testSchedulerPutGet() {
    Scheduler scheduler;

    // Prepare test elevator data.
    e_struct testData = {};
    testData.floor_number = 5;
    testData.car_to_floor_number = 10;
    testData.floor_up_button = true;
    testData.floor_down_button = false;
    testData.arrived = 0;

    std::tm testTime = {};
    testTime.tm_hour = 12;
    testTime.tm_min = 30;
    testTime.tm_sec = 0;
    testData.datetime = testTime;

    // This will hold the value received from get().
    e_struct resultData = {};

    // Launch a thread to invoke get().
    std::thread getter([&scheduler, &resultData]() {
        resultData = scheduler.get();
    });

    // Pause for 1s.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Insert the test data into the scheduler.
    scheduler.put(testData, 1);

    // Wait for the getter thread to finish.
    getter.join();

    // Validate that the received data matches what was sent.
    assert(resultData.floor_number == testData.floor_number);
    assert(resultData.car_to_floor_number == testData.car_to_floor_number);
    assert(resultData.floor_up_button == testData.floor_up_button);
    assert(resultData.floor_down_button == testData.floor_down_button);
    assert(resultData.arrived == testData.arrived);

    // Validate datetime fields.
    assert(resultData.datetime.tm_hour == testData.datetime.tm_hour);
    assert(resultData.datetime.tm_min == testData.datetime.tm_min);
    assert(resultData.datetime.tm_sec == testData.datetime.tm_sec);
}

int main() {
    std::cout << "==== TEST 1: Format Time from Floor.cpp ====" << std::endl;
    testFloorFormatTime();
    std::cout << "TEST 1 PASSED." << std::endl;

    std::cout << "==== TEST 2: Put/Get from Scheduler.cpp ====" << std::endl;
    testSchedulerPutGet();
    std::cout << "TEST 2 PASSED." << std::endl;

    std::cout << "==== TEST 3: Get/Set Current Floor from Elevator.cpp ====" << std::endl;
    testElevatorSetGetCurrentFloor();
    std::cout << "TEST 3 PASSED." << std::endl;

    return 0;
}
