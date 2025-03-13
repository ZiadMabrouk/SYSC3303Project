add_library(source Elevator.cpp Floor.cpp Scheduler.cpp)
target_include_directories(source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})