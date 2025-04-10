//
// Created by ziadm on 2025-01-31.
//

#ifndef ELEVATORDATATYPES_H
#define ELEVATORDATATYPES_H
#include <ctime>
#include <cstdint>
#include <cstring>
#include <string>

#define PORT 5000
#define MAX_CAPACITY 3

enum Direction { UP, DOWN, IDLE, BROKEN};

inline std::string stringDirection(Direction direction) {
    switch (direction) {
        case UP: return "UP";
        case DOWN: return "DOWN";
        case IDLE: return "IDLE";
        case BROKEN: return "BROKEN";
        default: return "UNKNOWN";
    }
}

typedef struct ElevatorData {
    tm datetime{};  // Initialize to zero
    short int floor_number = 0;
    bool floor_up_button = false;
    bool floor_down_button = false;
    int arrived = 0;
    bool acknowledged = false;
    short int car_to_floor_number = 0;
    int elevatorID = 0;
    int transmittedFloor = 0;
    Direction direction = Direction::IDLE;
    bool stateTest = false;
    bool broken = false;
    bool doorJammed = false;
    int capacity = 0;
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
