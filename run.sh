g++ src/Elevator.cpp src/Elevator.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Elevator.o
g++ src/Floor.cpp src/Floor.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Floor.o
g++ src/Scheduler.cpp src/Scheduler.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Scheduler.o
cd builds
gnome-terminal -- bash -c "./Scheduler.o 3; exec bash"
gnome-terminal -- bash -c "./Elevator.o 1; exec bash"
gnome-terminal -- bash -c "./Elevator.o 2; exec bash"
gnome-terminal -- bash -c "./Elevator.o 3; exec bash"
gnome-terminal -- bash -c "./Floor.o; exec bash"