#g++ src/Elevator.cpp src/Elevator.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Elevator.o
#g++ src/Floor.cpp src/Floor.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Floor.o
#g++ src/Scheduler.cpp src/Scheduler.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Scheduler.o
cd build/src
gnome-terminal -- bash -c "./Scheduler 3; exec bash"
gnome-terminal -- bash -c "./Elevator 1; exec bash"
gnome-terminal -- bash -c "./Elevator 2; exec bash"
gnome-terminal -- bash -c "./Elevator 3; exec bash"
gnome-terminal -- bash -c "./Floor; exec bash"