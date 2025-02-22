//
// Created by ziadm on 2025-01-30.
//

#include "Floor.h"
#include <chrono>
#include <thread>

#include <random>
#include <mutex>
#include <condition_variable>
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>

tm Floor::formatTime(const std::string& str) {

    tm datetime{};
    datetime.tm_hour = atoi(str.substr(0, 2).c_str());
    datetime.tm_min = atoi(str.substr(3, 2).c_str());
    datetime.tm_sec = atoi(str.substr(6, 2).c_str());

    return datetime;
}

void Floor::operator()(const std::string& fileLocation) {
    std::ifstream file(fileLocation);
    elevatorData data;

    std::string line, token;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::getline(ss, token, ' ');
        data.datetime = formatTime(token);

        std::getline(ss, token, ' ');
        data.floor_number = atoi(token.c_str());

        std::getline(ss, token, ' ');
        if (token == "Up") {
            data.floor_up_button = true;
            data.floor_down_button = false;
        } else if (token == "Down") {
            data.floor_up_button = false;
            data.floor_down_button = true;
        }

        scheduler.put(data);
    }
}





