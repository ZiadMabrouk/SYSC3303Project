CXX = g++
CC  = $(CXX)

DSTS = builds/Floor builds/Elevator builds/Scheduler
OBJS = builds/Floor.o builds/Elevator.o builds/Scheduler.o
all: builds $(DSTS)

clean:
	rm $(DSTS) $(OBJS)

builds:
	mkdir -p builds

builds/Floor: builds/Floor.o
builds/Elevator: builds/Elevator.o
builds/Scheduler: builds/Scheduler.o

builds/Floor.o: src/Floor.cpp src/Floor.h src/Datagram2.h src/ElevatorDataTypes.h
	$(CXX) -c src/Floor.cpp -o builds/Floor.o

builds/Elevator.o: src/Elevator.cpp src/Elevator.h src/Datagram2.h src/ElevatorDataTypes.h
	$(CXX) -c src/Elevator.cpp -o builds/Elevator.o

builds/Scheduler.o: src/Scheduler.cpp src/Datagram2.h src/ElevatorDataTypes.h src/Scheduler.h
	$(CXX) -c src/Scheduler.cpp -o builds/Scheduler.o