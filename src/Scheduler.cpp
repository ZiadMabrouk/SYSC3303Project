//
// Created by ziadm on 2025-01-30.
//
#include <chrono>
#include <thread>
#include <iostream>
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

Scheduler::Scheduler() : empty(true), mtx(), cv() {}

void Scheduler::put(e_struct elevatorData) {


    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    while ( !empty ) cv.wait(lock);

    std::ostringstream oss;

    // Format time as hh:mm:ss.mmm
    oss << std::setfill('0') 
        << std::setw(2) << elevatorData.datetime.tm_hour << ":"
        << std::setw(2) << elevatorData.datetime.tm_min << ":"
        << std::setw(2) << data.datetime.tm_sec << "."
        << std::setw(3) << data.milliseconds;

    // Format the rest of the string
    oss << " " << elevatorData.floor_number << " "
        << (elevatorData.floor_up_button ? "Up" : elevatorData.floor_down_button ? "Down" : "No Button");

    std::string newLine = oss.str();

    // Open the file in append mode
    std::ofstream outputFile("../lib/shareddata.txt", std::ios_base::app);
    if (!outputFile) {
        std::cerr << "File could not be opened for appending." << std::endl;
        return;
    }

    // Write the new line to the end of the file
    outputFile << newLine << std::endl;

    outputFile.close


    empty = false;
    cv.notify_all();
}

e_struct Scheduler::get() {
    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    while ( empty ) cv.wait(lock);
    std::ifstream f("../lib/shareddata.txt");

        // Check if the file is successfully opened
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
        return 1;
    }



    std::vector<std::string> lines;
    std::string line;
    std::string firstLine;

    // Read the first line separately
    if (std::getline(inputFile, firstLine)) {
        // Read all remaining lines
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }
    }
    inputFile.close();

    // Write remaining lines back to the file
    std::ofstream outputFile("../lib/shareddata.txt");
    if (!outputFile) {
        std::cerr << "File could not be opened for writing." << std::endl;
        return;
    }

    for (const auto& l : lines) {
        outputFile << l << std::endl;
    }
    outputFile.close();
    

    if (lines.empty()) {
        empty = true; 
    }

    
    e_struct data;
    std::istringstream iss(firstLine);
    std::string timeString;
    std::string floorButton;

    // Extract time, floor number, and button status from the string
    iss >> timeString >> data.floor_number >> floorButton;

    // Parse time (hh:mm:ss.mmm)
    sscanf(timeString.c_str(), "%2d:%2d:%2d.%3d", 
           &data.datetime.tm_hour, 
           &data.datetime.tm_min, 
           &data.datetime.tm_sec, 
           &data.milliseconds);

    // Set button status
    data.floor_up_button = (floorButton == "Up");
    data.floor_down_button = (floorButton == "Down");

    
    cv.notify_all();
    return data;
}
void Scheduler::operator()() {
    while (1) {}
}


int main(void) {

    Scheduler scheduler; 
// Test struct 1
    ElevatorData test1;
    test1.datetime = {0, 30, 14, 1, 0, 125}; // 2025-01-01 14:30:00
    test1.floor_number = 1;
    test1.floor_up_button = true;
    test1.floor_down_button = false;

    // Test struct 2
    ElevatorData test2;
    test2.datetime = {500, 45, 16, 1, 1, 125}; // 2025-02-01 16:45:00.500
    test2.floor_number = 5;
    test2.floor_up_button = false;
    test2.floor_down_button = true;

    // Test struct 3
    ElevatorData test3;
    test3.datetime = {750, 15, 9, 1, 2, 125}; // 2025-03-01 09:15:00.750
    test3.floor_number = 10;
    test3.floor_up_button = true;
    test3.floor_down_button = false;

    scheduler.put(test1)
    scheduler.put(test2)
    scheduler.put(test3)

    e_struct outtest1 = scheduler.get();
    e_struct outtest2 =scheduler.get();
    e_struct outtest3 = scheduler.get();
    std::cout << "Success"; 
    return 1;
}
