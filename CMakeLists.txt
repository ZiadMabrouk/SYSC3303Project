cmake_minimum_required(VERSION 3.22.1)
project(SYSC3303Project)



set(CMAKE_CXX_STANDARD 20)

add_executable(SYSC3303Project src/main.cpp
        src/Elevator.cpp
        src/Elevator.h
        src/Scheduler.cpp
        src/Datagram2.h
        src/Scheduler.h
        src/Floor.cpp
        src/Floor.h
        src/ElevatorDataTypes.h)
