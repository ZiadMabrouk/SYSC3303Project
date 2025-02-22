#include <mutex>
#include <condition_variable>
#include "ElevatorDataTypes.h"
#include "Scheduler.h"

void Scheduler::put(elevatorData data) {
    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.

    dataQueue.push(data);
    empty = false;

    cv.notify_all();
}

elevatorData Scheduler::get() {
    std::unique_lock<std::mutex> lock(mtx);	// releases when lock goes out of scope.
    while ( empty ) cv.wait(lock);

    elevatorData data = dataQueue.front();
    dataQueue.pop();
    empty = dataQueue.empty();

    cv.notify_all();
    return data;
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
