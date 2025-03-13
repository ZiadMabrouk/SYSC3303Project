//
// Created by ziadm on 2025-01-30.
//

#ifndef FLOOR_H
#define FLOOR_H

#include "Scheduler.h"
#include "ElevatorDataTypes.h"
#include "Datagram2.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include <fstream>



class Floor {

public:
    Floor();

    DatagramSocket receiveSocket;
    DatagramSocket sendSocket;

    void readFile();

    tm formatTime(const std::string& str);

    void operator()();
};


#endif //FLOOR_H
