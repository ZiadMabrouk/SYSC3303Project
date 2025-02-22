#ifndef ELEVATORSUBSYSTEM_H
#define ELEVATORSUBSYSTEM_H

#include "Scheduler.h"
#include "ElevatorDataTypes.h"
#include "Elevator.h"

class ElevatorSubsystem
{
private:
    Scheduler& scheduler;
    Elevator& elevator;
public:
    explicit ElevatorSubsystem(Scheduler& scheduler, Elevator& elevator) : scheduler(scheduler), elevator(elevator) {
    };

    void operator()();

};

#endif //ELEVATORSUBSYSTEM_H
