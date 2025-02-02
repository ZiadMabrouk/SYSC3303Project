#include <iostream>

#include "Floor.h"
#include "Scheduler.h"

int main() {
    Scheduler scheduler;
    Floor floor(scheduler);

    std::thread floor_thread( floor);
    floor_thread.join();

    return 0;
}
