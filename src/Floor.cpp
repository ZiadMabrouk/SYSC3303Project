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

//

// this method reads a line from the input file and converts it into e_struct then invokes put into the scheduler object.
void Floor::readFile() {
    std::ifstream file("../data/tests/testcase.txt");//open the file for reading
    e_struct elevatorData;

    std::string line, token;
    while (std::getline(file, line)) { //read each from file and store into line
        std::stringstream ss(line);

        std::getline(ss, token, ' ');// read first word in that line
        if (token == "Elevator") {
            std::cout << ss.str() << std::endl;
            elevatorData.elevatorID = -10;
            elevatorData.broken = true;
            send_and_wait_for_ack("Floor", elevatorData, PORT, receiveSocket, sendSocket);
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        } else if (token == "Doors") {
            std::cout << ss.str() << std::endl;
            elevatorData.elevatorID = -20;
            elevatorData.doorJammed = true;
            send_and_wait_for_ack("Floor", elevatorData, PORT, receiveSocket, sendSocket);
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        } else {
            elevatorData.datetime = formatTime(token);
            elevatorData.broken = false;
            elevatorData.doorJammed = false;
        }

        std::getline(ss, token, ' ');
        if (atoi(token.c_str()) > numFloors || atoi(token.c_str()) < 1) {
            std::cout << "Invalid floor number: " << atoi(token.c_str()) << std::endl;
            std::cout << "Skipping this line in the input file..." << std::endl;
            continue;
        }
        elevatorData.floor_number = atoi(token.c_str());
        std::cout << "Floor Number: " << elevatorData.floor_number << std::endl;

        std::getline(ss, token, ' ');
        if (token == "Up") {
            elevatorData.floor_up_button = true;
            elevatorData.floor_down_button = false;
        } else if (token == "Down") {
            elevatorData.floor_up_button = false;
            elevatorData.floor_down_button = true;
        }

        std::getline(ss, token, ' ');
        if (atoi(token.c_str()) > numFloors || atoi(token.c_str()) < 1) {
            std::cout << "Invalid destination floor number: " << atoi(token.c_str()) << std::endl;
            std::cout << "Skipping this line in the input file..." << std::endl;
            continue;
        }
        elevatorData.car_to_floor_number = atoi(token.c_str());

        elevatorData.elevatorID = -1; // Helps discern that this e_struct is just data read from a file and not actual elevator data.

        send_and_wait_for_ack("Floor", elevatorData, PORT, receiveSocket, sendSocket);
        std::this_thread::sleep_for(std::chrono::seconds(1));
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



