#include <cassert>
#include <iostream>
#include <ostream>
#include <thread>

#include "../src/ElevatorDataTypes.h"
#include "../src/Elevator.h"
#include "../src/Scheduler.h"
#include "../src/Floor.h"


#include <catch2/catch_test_macros.hpp>
//
TEST_CASE("State Machines (Scheduler) - handle() ", "[StateMachine]") {
    DatagramSocket sendSocket;
    DatagramSocket receiveSocket;

    Scheduler scheduler(5);
    SECTION("Scheduler starts in WaitingForInput state"){
        WaitingForInput* castedState = dynamic_cast<WaitingForInput *>(scheduler.currentState);
        REQUIRE(castedState != nullptr);
    }

    SECTION("Scheduler goes into Dispatching after receiving message") {
        e_struct testStruct;
        testStruct.elevatorID = -1;
        testStruct.stateTest = true;

        send_no_wait("TestSender", testStruct, 5000, receiveSocket, sendSocket);
        scheduler.handle();
        Dispatching* castedState2 = dynamic_cast<Dispatching *>(scheduler.currentState);
        REQUIRE(castedState2 != nullptr);
    }
}
TEST_CASE("State Machines (Elevator) - Inital State ", "[StateMachine]") {
    Elevator elevator(5);
    SECTION("Elevator starts in WaitingForInput state") {
        eWaitingForInput* castedState = dynamic_cast<eWaitingForInput *>(elevator.currentState);
        REQUIRE(castedState != nullptr);
    }
    SECTION("Elevator goes into ProcessingRequest after receiving message") {
        elevator.myQueue.push_back(5);
        elevator.stateTest = true;
        elevator.handle();
        ProcessRequest* castedState2 = dynamic_cast<ProcessRequest *>(elevator.currentState);
        REQUIRE(castedState2 != nullptr);
    }

}

TEST_CASE("UDP Communication (Scheduler) - Socket.send() - Socket.receive()", "[UDP]") {
    DatagramSocket sendSocket;
    DatagramSocket receiveSocket(5000);

    e_struct testStruct;
    testStruct.transmittedFloor = 9;
    send_no_wait("TestSender", testStruct, 5000, receiveSocket, sendSocket);
    e_struct receivedStruct = receive_no_wait("TestReceiver", receiveSocket, sendSocket);
    REQUIRE(receivedStruct.transmittedFloor == 9);
}

TEST_CASE("UDP Communication (Elevator) - Socket.send() - Socket.receive()", "[UDP]") {
    DatagramSocket sendSocket;
    DatagramSocket receiveSocket(5001);

    e_struct testStruct;
    testStruct.transmittedFloor = 9;
    send_no_wait("TestSender", testStruct, 5001, receiveSocket, sendSocket);
    e_struct receivedStruct = receive_no_wait("TestReceiver", receiveSocket, sendSocket);
    REQUIRE(receivedStruct.transmittedFloor == 9);
}


TEST_CASE("Algorithm - Scheduler ", "[Algorithm]") {
    //TODO: Fill this out with Daniel

}
//Created by Jinan
TEST_CASE("ElevatorTest - getCurrentFloor()", "[Calculator]") {
    Scheduler scheduler(5);
    Elevator elevator(1);
    int floorToSet = 5;
    REQUIRE(floorToSet == 5);
    elevator.setCurrentFloor(floorToSet);
    int floor = elevator.getCurrentFloor();
    REQUIRE(floor == 5);

}
//Created by Jinan
// Given Input: 14:15:47.876, Expected Output: tm object with hours, mins and secs formatted into it.
TEST_CASE("FloorTest - Subsystem", "[Floor]") {
    Scheduler scheduler(3);
    Floor floor;

    tm time = floor.formatTime("14:15:47.876");

    REQUIRE(time.tm_hour == 14);
    REQUIRE(time.tm_min == 15);
    REQUIRE(time.tm_sec == 47);
}


//Created by Jinan
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