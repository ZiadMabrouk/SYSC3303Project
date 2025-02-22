#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Scheduler.h"
#include "ElevatorDataTypes.h"

enum ElevatorState {
    STOPPED,
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    OPENING,
    OPEN,
    BUTTON_PRESSED,
    CLOSING,
};

class Elevator
{
private:
    ElevatorState state;
    Scheduler& scheduler;
    elevatorData data;
    int floorNumber;
public:
    Elevator(Scheduler& scheduler) : state(IDLE), scheduler(scheduler), floorNumber(1) {};

    void operator()();

    ElevatorState getState();

    void setState(ElevatorState state);
};

#endif //ELEVATOR_H
