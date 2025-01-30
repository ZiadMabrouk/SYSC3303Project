//
// Created by ziadm on 2025-01-30.
//

#include "Elevator.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>

#include <condition_variable>

#include "Scheduler.h"

void Elevator<>::operator()(const std::string &name) {
    for(int i = 0; i < 10; i++) {
        std::cout << name << "(" << std::this_thread::get_id() << ") ready to consume " << i << std::endl;
        Type item = scheduler.get();
        std::cout << name << "(" << std::this_thread::get_id() << ") consumed " << item << std::endl;
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    }
}