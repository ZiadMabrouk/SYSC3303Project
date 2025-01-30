cmake_minimum_required(VERSION 3.30)
project(SYSC3303Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(SYSC3303Project main.cpp
        Elevator.cpp
        Elevator.h
        Scheduler.cpp
        Scheduler.h
        Floor.cpp
        Floor.h)
