#include <cassert>
#include <iostream>
#include <ostream>
#include <thread>

#include "../src/ElevatorDataTypes.h"
#include "../src/Elevator.h"
#include "../src/Scheduler.h"
#include "../src/Floor.h"

int main() {
    std::cout << "==== TEST 1: Format Time from Floor.cpp ====" << std::endl;

    Scheduler scheduler1;
    Floor floor1(scheduler1);
    std::cout << "Given Input: 14:15:47.876, Expected Output: tm object with hours, mins and secs formatted into it." << std::endl;

    tm time = floor1.formatTime("14:15:47.876");

    assert(time.tm_hour == 14);
    assert(time.tm_min == 15);
    assert(time.tm_sec == 47);

    std::cout << "TEST 1 PASSED." << std::endl;

    return 0;
}
