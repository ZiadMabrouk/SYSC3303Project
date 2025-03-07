//
// Created by ziadm on 2025-01-31.
//

#ifndef ELEVATORDATATYPES_H
#define ELEVATORDATATYPES_H
#include <ctime>
#include <iostream>

enum Direction { UP, DOWN, IDLE };
enum MessageType { STATUS_UPDATE, DISPATCH_COMMAND, FLOOR_REQUEST };

typedef struct ElevatorData {
    tm datetime; // datetime data type: https://www.w3schools.com/cpp/cpp_date.asp
    short int floor_number; // 2 bytes long (more than enough)
    bool floor_up_button; // The button to request an elevator to go up *Note: The top and bottom floors will only use one button
    bool floor_down_button; // The button to request an elevator to go down
    int arrived;
    short int car_to_floor_number;
}e_struct;

typedef struct ElevatorMessage {
    int elevatorNumber;
    int currentFloor;
    Direction direction;
} elevatorMessage;


#endif //ELEVATORDATATYPES_H
