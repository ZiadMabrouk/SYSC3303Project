//
// Created by ziadm on 2025-01-30.
//

#include "Floor.h"
#include <chrono>
#include <thread>

#include <random>
#include "ElevatorDataTypes.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>

#define FLOOR_TIME 5

// this method reads a line from the input file and converts it into e_struct then invokes put into the scheduler object.
void Floor::readFile() {
    std::ifstream file("../data/tests/testcase.txt");//open the file for reading
    e_struct elevatorData;

    std::string line, token;
    while (std::getline(file, line)) { //read each from file and store into line
        std::stringstream ss(line);

        elevatorData.requestType = FLOOR;

        std::getline(ss, token, ' ');// read first word in that line
        elevatorData.datetime = formatTime(token);


        std::getline(ss, token, ' ');
        if (atoi(token.c_str()) > numFloors || atoi(token.c_str()) < 1) {
            std::cout << "Invalid floor number: " << atoi(token.c_str()) << std::endl;
            std::cout << "Skipping this line in the input file..." << std::endl;
            continue;
        }
        elevatorData.floorNumber = atoi(token.c_str());
        std::cout << "Floor Number: " << elevatorData.floorNumber << std::endl;

        std::getline(ss, token, ' ');
        if (token == "Up") {
            elevatorData.floorDirection = UP;
        } else {
            elevatorData.floorDirection = DOWN;
        }

        std::getline(ss, token, ' ');
        if (atoi(token.c_str()) > numFloors || atoi(token.c_str()) < 1) {
            std::cout << "Invalid destination floor number: " << atoi(token.c_str()) << std::endl;
            std::cout << "Skipping this line in the input file..." << std::endl;
            continue;
        }
        elevatorData.destinationFloorNumber = atoi(token.c_str());

        std::getline(ss, token, ' ');
        if (token == "Stuck") {
            elevatorData.fault = DOOR_STUCK;
        } else if (token == "Timer") {
            elevatorData.fault = TIMER;
        }else {
            elevatorData.fault = NONE;
        }

        send_and_wait_for_ack("Floor", elevatorData, PORT, receiveSocket, sendSocket);
        std::this_thread::sleep_for(std::chrono::seconds(FLOOR_TIME));
    }
}

tm Floor::formatTime(const std::string& str) {

    tm datetime{};
    datetime.tm_hour = atoi(str.substr(0, 2).c_str());
    datetime.tm_min = atoi(str.substr(3, 2).c_str());
    datetime.tm_sec = atoi(str.substr(6, 2).c_str());

    return datetime;
}
#ifndef UNIT_TEST
// invokes the readFile() method.
int main(int argc, char *argv[]) {
    Floor floor(std::atoi(argv[1]));
    floor.readFile();
}
#endif



