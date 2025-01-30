//
// Created by ziadm on 2025-01-30.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include "Floor.h"
#include "Scheduler.h"


template <typename Type> class Floor
{
private:
    std::string name;
    Scheduler<Type>& scheduler;

public:
    Floor( Scheduler<Type>& a_scheduler ) : name(), scheduler(a_scheduler) {}

    void operator()( const std::string& name ) {
        for(int i = 0; i < 10; i++) {
            std::cout << name << "(" << std::this_thread::get_id() << ") produced " << i << std::endl;
            scheduler.put( i );
            std::cout << name << "(" << std::this_thread::get_id() << ") put in box " << i << std::endl;
            std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
        }
    }
};
