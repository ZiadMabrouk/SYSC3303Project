//
// Created by ziadm on 2025-01-30.
//

#include "Elevator.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>
#include <string>
#include <random>
#include <mutex>
#include <ctime> // For datetime data type 
#include <condition_variable>
#include "ElevatorDataTypes.h"
#include "Scheduler.h"

typedef struct ElevatorDataStruct {

    std::tm datetime; // datetime data type: https://www.w3schools.com/cpp/cpp_date.asp
    short int floor_number; // 2 bytes long (more than enough)
    bool floor_up_button; // The button to request an elevator to go up *Note: The top and bottom floors will only use one button
    bool floor_down_button // The button to request an elevator to go down

}e_struct;

Scheduler.get();

class Elevator {
public:
    Elevator(int id, queue<e_struct>* schedulerQueue, queue<string>* elevatorQueue, mutex* mtx, condition_variable* cv)
            : id(id), schedulerQueue(schedulerQueue), elevatorQueue(elevatorQueue), mtx(mtx), cv(cv), stop(false) {}

    void operator()() {
        while (true) {
            unique_lock<mutex> lock(*mtx);
            cv->wait(lock, [this] { return !schedulerQueue->empty() || stop; });

            if (stop && schedulerQueue->empty()) break;

            e_struct request = schedulerQueue->front();
            schedulerQueue->pop();
            lock.unlock();

            cout << "Elevator " << id << " received request: Floor " << request.floor_number << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Simulate travel time

            lock.lock();
            string response = "Elevator " + to_string(id) + " completed request on floor " + to_string(request.floor_number);
            elevatorQueue->push(response);
            lock.unlock();
            cv->notify_all();
        }
    }

    void stopElevator() {
        stop = true;
    }

private:
    int id;
    queue<e_struct>* schedulerQueue;
    queue<string>* elevatorQueue;
    mutex* mtx;
    condition_variable* cv;
    bool stop;
};

int main() {
    queue<e_struct> schedulerToElevator;
    queue<string> elevatorToScheduler;
    mutex mtx;
    condition_variable cv;

    Elevator elevator1(1, &schedulerToElevator, &elevatorToScheduler, &mtx, &cv);
    thread elevatorThread(ref(elevator1));

    {
        unique_lock<mutex> lock(mtx);
        e_struct request;
        time_t now = time(0);
        request.datetime = *localtime(&now);
        request.floor_number = 5;
        request.floor_up_button = true;
        request.floor_down_button = false;

        schedulerToElevator.push(request);
    }
    cv.notify_all();

    this_thread::sleep_for(chrono::seconds(1));

    {
        unique_lock<mutex> lock(mtx);
        if (!elevatorToScheduler.empty()) {
            cout << elevatorToScheduler.front() << endl;
            elevatorToScheduler.pop();
        }
    }

    elevator1.stopElevator();
    cv.notify_all();
    elevatorThread.join();

    return 0;
}




