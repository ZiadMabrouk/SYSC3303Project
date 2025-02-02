//
// Created by ziadm on 2025-01-30.
//

#include "Scheduler.h"

Scheduler::Scheduler() : empty(true), mtx(), cv() {}

void Scheduler::put(e_struct elevatorData) {
    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    while ( !empty ) cv.wait(lock);

    empty = false;
    cv.notify_all();
}

void Scheduler::get() {
    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    while ( empty ) cv.wait(lock);

    empty = true;
    cv.notify_all();
    return;
}
