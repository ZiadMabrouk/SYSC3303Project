//
// Created by ziadm on 2025-01-30.
//

#include "Scheduler.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include "ElevatorDataTypes.h"

class Scheduler
{
private:
    bool empty = true;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
public:
    Scheduler() : empty(true), mtx(), cv() {}	// Constructor

    void put(  ) {
        std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
        while ( !empty ) cv.wait(lock);

        empty = false;
        cv.notify_all();
    }

    void get() {
        std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
        while ( empty ) cv.wait(lock);

        empty = true;
        cv.notify_all();
        return;
    }
};