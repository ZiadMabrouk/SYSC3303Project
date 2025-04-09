g++ src/Elevator.cpp src/Elevator.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Elevator.o
g++ src/Floor.cpp src/Floor.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Floor.o
g++ src/Scheduler.cpp src/Scheduler.h src/Datagram2.h src/ElevatorDataTypes.h -o builds/Scheduler.o
cd builds

DEFAULT_ELEVATORS=1
DEFAULT_FLOORS=22
INPUT_FILE="SamTestCase.txt"

NUM_ELEVATORS=${1:-$DEFAULT_ELEVATORS}
NUM_FLOORS=${2:-$DEFAULT_FLOORS}

gnome-terminal -- bash -c "./Scheduler.o $NUM_ELEVATORS; exec bash"

for ((i=1; i<=NUM_ELEVATORS; i++))
do
  gnome-terminal -- bash -c "./Elevator.o $i; exec bash"
done

gnome-terminal -- bash -c "./Floor.o $NUM_FLOORS $INPUT_FILE; exec bash"