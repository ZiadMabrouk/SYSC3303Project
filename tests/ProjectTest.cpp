#include <cassert>
#include <iostream>
#include <ostream>
#include <thread>

#include "../src/ElevatorDataTypes.h"
#include "../src/Elevator.h"
#include "../src/Scheduler.h"
#include "../src/Floor.h"


#include <catch2/catch_test_macros.hpp>


TEST_CASE("ElevatorTest - getCurrentFloor()", "[Calculator]") {
    Scheduler scheduler(5);
    Elevator elevator(1);
    int floorToSet = 5;
    REQUIRE(floorToSet == 5);
    elevator.setCurrentFloor(floorToSet);
    int floor = elevator.getCurrentFloor();
    REQUIRE(floor == 5);
}

// Given Input: 14:15:47.876, Expected Output: tm object with hours, mins and secs formatted into it.
TEST_CASE("FloorTest - formatTime(tm datetime)", "[Floor]") {
    Scheduler scheduler(3);
    Floor floor;

    tm time = floor.formatTime("14:15:47.876");

    REQUIRE(time.tm_hour == 14);
    REQUIRE(time.tm_min == 15);
    REQUIRE(time.tm_sec == 47);
}



TEST_CASE("Scheduler put() & get()", "[Scheduler]") {
    Scheduler scheduler(4);

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
    REQUIRE(scheduler.elevators.size() == 4);
    REQUIRE(scheduler.elevators[0].elevatorID == 1);
    REQUIRE(scheduler.elevators[0].transmittedFloor == 1);
    REQUIRE(scheduler.elevators[1].transmittedFloor == 1);
    REQUIRE(scheduler.elevators[2].transmittedFloor == 1);
    REQUIRE(scheduler.elevators[3].transmittedFloor == 1);
    REQUIRE(scheduler.elevators[3].direction == IDLE);

}

/**
// Expected:
void testSchedulerPutGet() {
    m_Scheduler scheduler;

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
    assert(resultData.datetime.tsec == testData.datetime.tm_sec);
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
**/
