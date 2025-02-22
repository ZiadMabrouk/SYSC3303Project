#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <mutex>
#include <condition_variable>
#include <queue>

#include "ElevatorDataTypes.h"


class Scheduler
{
private:
    bool empty;	// The state of the box.
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<elevatorData> dataQueue;
public:
    Scheduler() : empty(true) {}

    void put(elevatorData data);

    elevatorData get();

    void operator()();
    
};


#endif //SCHEDULER_H
