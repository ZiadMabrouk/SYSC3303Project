//
// Created by ziadm on 2025-01-31.
//

#ifndef ELEVATORDATATYPES_H
#define ELEVATORDATATYPES_H
#include <ctime>
#include <cstdint>
#include <cstring>

enum Direction { UP, DOWN, IDLE };

typedef struct ElevatorData {
    tm datetime; // datetime data type: https://www.w3schools.com/cpp/cpp_date.asp
    short int floor_number; // 2 bytes long (more than enough)
    bool floor_up_button; // The button to request an elevator to go up *Note: The top and bottom floors will only use one button
    bool floor_down_button; // The button to request an elevator to go down
    int arrived;
    bool acknowledged;
    short int car_to_floor_number;
    int elevatorID;
    int transmittedFloor;
    Direction direction;
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
