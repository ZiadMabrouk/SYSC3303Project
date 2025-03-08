//
// Created by ziadm on 2025-01-31.
//

#ifndef ELEVATORDATATYPES_H
#define ELEVATORDATATYPES_H
#include <ctime>
#include <cstdint>
#include <cstring>

#define PORT 5000

enum Direction { UP, DOWN, IDLE };

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
