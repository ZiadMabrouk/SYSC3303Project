//
// Created by ziadm on 2025-01-31.
//

#ifndef ELEVATORDATATYPES_H
#define ELEVATORDATATYPES_H
#include <ctime>
#include <cstdint>
#include <cstring>

#define PORT 5000
#define SCHEDULER_RECEIVE_PORT 8000 // only elevators will send to this port

enum Direction { UP, DOWN, IDLE};
enum Fault {NONE, DOOR_STUCK, TIMER};
enum RequestType {FLOOR, ELEVATOR};

typedef struct ElevatorData {
    RequestType requestType = ELEVATOR;
    int elevatorID = 0;
    tm datetime{};
    short int floorNumber = 0;
    Direction floorDirection = UP;
    short int destinationFloorNumber = 0;
    Fault fault = NONE;
    int transmittedFloor = 0;
    Direction direction = Direction::IDLE;
    bool stateTest = false;
    // Serialize struct into byte array
    void serialize(uint8_t* buffer) const {
        std::memcpy(buffer, this, sizeof(ElevatorData));
    }

    // Deserialize byte array into struct
    static ElevatorData deserialize(const uint8_t* buffer) {
        ElevatorData data;
        std::memcpy(&data, buffer, sizeof(ElevatorData));
        return data;
    }


}e_struct;


#endif //ELEVATORDATATYPES_H
