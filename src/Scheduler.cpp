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
#include <fstream>

Scheduler::Scheduler() : empty(true), mtx(), cv() {} // proper definition of the Scheduler constructor


// returns void takes in our elevator Data type, formats the data type into a string then, appends to output file
// shareddata.txt and changes the status of scheduler instance from empty to not empty.
void Scheduler::put(e_struct elevatorData) {


    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    //while ( !empty ) cv.wait(lock);

    // This segment of the code  is the beginning of the string formating
    std::ostringstream oss; //creates an oss stream which can be turned into a string

    // Format time as hh:mm:ss.mmm
    oss << std::setfill('0')
        << std::setw(2) << elevatorData.datetime.tm_hour << ":"
        << std::setw(2) << elevatorData.datetime.tm_min << ":"
        << std::setw(2) << elevatorData.datetime.tm_sec;

    // Format the rest of the string
    oss << " " << elevatorData.floor_number << " "
        << (elevatorData.floor_up_button ? "Up" : elevatorData.floor_down_button ? "Down" : "No Button");

    // What I added in should account for the floor number people are going into
    oss << " " << elevatorData.car_to_floor_num;


    std::string newLine = oss.str(); // formats the oss stream into a string

    //end of the string formating

	//std::string newLine = "12:23:12 4 Up";
    // Open the file in append mode
    std::ofstream outputFile("../data/shared/shareddata.txt", std::ios_base::app); // returns 1 on success
    if (!outputFile) {
        std::cerr << "File could not be opened for appending." << std::endl;
        return;
    }

    //std::cout << newLine <<"\n"; // check if this works, It does work so proble is with get.


    // Write the new line(formatted string along with \n) to the end of the file
    outputFile << newLine << std::endl;

    outputFile.close(); // closes the file


    empty = false; // changes the status of the scheduler to not be empty
    cv.notify_all(); // notifies other threads that are in the blocked set to be able to be scheduled.
}


e_struct Scheduler::get() {
    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    while ( empty ) cv.wait(lock); // only go to next line if sched object is not empty.
    std::ifstream f("../data/shared/shareddata.txt");

        // Check if the file is successfully opened note if block only triggers if not opened.
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
		e_struct struct1;
        return  struct1;
    }



    std::vector<std::string> lines; // create a vector of strings.
    std::string line;
    std::string firstLine;

    // Read the first line separately
    if (std::getline(f, firstLine)) { //read from f and write into firsLine, getline returns f probably only on success
        // Read all remaining lines
        while (std::getline(f, line)) {
            lines.push_back(line); // pushback line to the end of the vector
        }
    }
    f.close();

    // Write remaining lines back to the file
    std::ofstream outputFile("../data/shared/shareddata.txt");
    if (!outputFile) {
        std::cerr << "File could not be opened for writing." << std::endl;
		e_struct struct1;
        return  struct1;
    }

    // for every string in the vector
    for (const auto& l : lines) {
        outputFile << l << std::endl; // place them into the output file.
    }
    outputFile.close();


    if (lines.empty()) {
        empty = true; // if the vector of strings is empty , the sched object will be modified to be empty.
    }


    e_struct data;
    std::istringstream iss(firstLine);
    std::string timeString;
    std::string floorButton;

    // line I added

    // Extract time, floor number, and button status from the firstLine string
    iss >> timeString >> data.floor_number >> floorButton >> data.car_to_floor_num;


    // Parse time (hh:mm:ss.mmm)
    sscanf(timeString.c_str(), "%2d:%2d:%2d",
           &data.datetime.tm_hour,
           &data.datetime.tm_min,
           &data.datetime.tm_sec);

    // Set button status
    data.floor_up_button = (floorButton == "Up");
    data.floor_down_button = (floorButton == "Down");


    cv.notify_all();
    return data;
}
void Scheduler::operator()() {
    while (1) {}
}

/***
int main(void) {

    Scheduler scheduler;
// Test struct 1
    ElevatorData test1;
    test1.datetime = {30, 14, 1, 0, 125}; // 2025-01-01 14:30:00
    test1.floor_number = 1;
    test1.floor_up_button = true;
    test1.floor_down_button = false;

    // Test struct 2
    ElevatorData test2;
    test2.datetime = {45, 16, 1, 1, 125}; // 2025-02-01 16:45:00.500
    test2.floor_number = 5;
    test2.floor_up_button = false;
    test2.floor_down_button = true;

    // Test struct 3
    ElevatorData test3;
    test3.datetime = {15, 9, 1, 2, 125}; // 2025-03-01 09:15:00.750
    test3.floor_number = 10;
    test3.floor_up_button = true;
    test3.floor_down_button = false;

    scheduler.put(test1);
    scheduler.put(test2);
    scheduler.put(test3);

    e_struct outtest1 = scheduler.get();
    e_struct outtest2 =scheduler.get();
    e_struct outtest3 = scheduler.get();
    std::cout << "Success"; 
    return 1;
}
***/
