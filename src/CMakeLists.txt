add_library(source Elevator.cpp Floor.cpp Scheduler.cpp)
target_include_directories(source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(source PRIVATE UNIT_TEST)


# Add a new executable named "Scheduler"
add_executable(Scheduler Scheduler.cpp)

# Specify include directories for headers
target_include_directories(Scheduler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Include the headers explicitly (Scheduler.h, Datagram2.h, ElevatorDataTypes.h)
target_sources(Scheduler PRIVATE
        Scheduler.h
        Datagram2.h
        ElevatorDataTypes.h
)

# Add a new executable named "Scheduler"
add_executable(Elevator Elevator.cpp)

# Specify include directories for headers
target_include_directories(Elevator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Include the headers explicitly (Scheduler.h, Datagram2.h, ElevatorDataTypes.h)
target_sources(Elevator PRIVATE
        Elevator.h
        Datagram2.h
        ElevatorDataTypes.h
)

# Add a new executable named "Scheduler"
add_executable(Floor Floor.cpp)

# Specify include directories for headers
target_include_directories(Floor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Include the headers explicitly (Scheduler.h, Datagram2.h, ElevatorDataTypes.h)
target_sources(Floor PRIVATE
        Floor.h
        Datagram2.h
        ElevatorDataTypes.h
)