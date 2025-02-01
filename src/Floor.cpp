//
// Created by ziadm on 2025-01-30.
//

#include "Floor.h"



Floor::Floor(Scheduler& scheduler) : scheduler(scheduler) {}

void Floor::readFile() {
    std::ifstream file("../src/input_file.txt");

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void Floor::operator()() {
    readFile();
}





