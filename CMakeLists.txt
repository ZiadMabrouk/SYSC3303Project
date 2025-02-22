cmake_minimum_required(VERSION 3.30)
project(SYSC3303Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(SYSC3303Project src/main.cpp
        src/Elevator.cpp
        src/Elevator.h
        src/Scheduler.cpp
        src/Scheduler.h
        src/Floor.cpp
        src/Floor.h
        src/ElevatorDataTypes.h
        src/ElevatorSubsystem.h
        src/ElevatorSubsystem.cpp)
