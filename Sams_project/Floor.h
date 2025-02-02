//
// Created by ziadm on 2025-01-30.
//

#ifndef FLOOR_H
#define FLOOR_H

#include "Scheduler.h"
#include "ElevatorDataTypes.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include <fstream>



class Floor {
private:
    Scheduler& scheduler;
public:
    explicit Floor(Scheduler& scheduler) : scheduler(scheduler) {}

    void readFile();

    tm formatTime(const std::string& str);

    void operator()();
};


#endif //FLOOR_H
