cmake_minimum_required(VERSION 3.22.1)
project(SYSC3303Project)
enable_testing()
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Catch2)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(src)
add_subdirectory(tests)
#add_executable(SYSC3303Project
#        src/Elevator.cpp
#        src/Elevator.h
#        src/Scheduler.cpp
#        src/Datagram2.h
#        src/Scheduler.h
#        src/Floor.cpp
#        src/Floor.h
#        src/ElevatorDataTypes.h)
#target_link_libraries(SYSC3303Project PRIVATE source)
#target_compile_definitions(SYSC3303Project PRIVATE UNIT_TEST)

include(FetchContent)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.0.1
)
FetchContent_MakeAvailable(ftxui)

add_executable(UI src/Display.cpp src/Display.h)
target_link_libraries(UI
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)