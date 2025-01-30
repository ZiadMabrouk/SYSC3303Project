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

template <typename Type> class Scheduler
{
private:
    Type contents;	// The "Type" stored in the box
    bool empty = true;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
public:
    Scheduler() : contents(Type()), empty(true), mtx(), cv() {}	// Constructor

    void put( Type item ) {
        std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
        while ( !empty ) cv.wait(lock);
        contents = item;
        empty = false;
        cv.notify_all();
    }

    Type get() {
        std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
        while ( empty ) cv.wait(lock);
        Type item = contents;
        empty = true;
        cv.notify_all();
        return item;
    }
};
