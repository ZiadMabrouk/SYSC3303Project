//
// Created by ziadm on 2025-01-30.
//

#include "Floor.h"

void Floor::readFile() {
    std::ifstream file("../src/SamTestCase.txt");
    e_struct elevatorData;

    std::string line, token;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::getline(ss, token, ' ');
        elevatorData.datetime = formatTime(token);

        std::getline(ss, token, ' ');
        elevatorData.floor_number = atoi(token.c_str());

        std::getline(ss, token, ' ');
        if (token == "Up") {
            elevatorData.floor_up_button = true;
            elevatorData.floor_down_button = false;
        } else if (token == "Down") {
            elevatorData.floor_up_button = false;
            elevatorData.floor_down_button = true;
        }

        scheduler.put(elevatorData);
    }
}

tm Floor::formatTime(const std::string& str) {

    tm datetime{};
    datetime.tm_hour = atoi(str.substr(0, 2).c_str());
    datetime.tm_min = atoi(str.substr(3, 2).c_str());
    datetime.tm_sec = atoi(str.substr(6, 2).c_str());

    return datetime;
}

void Floor::operator()() {
    readFile();
}





