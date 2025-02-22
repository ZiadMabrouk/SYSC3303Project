
// this file defines the Elevator Data type structure shortened to e_struct

#ifndef ELEVATORDATATYPES_H
#define ELEVATORDATATYPES_H
#include <ctime>
#include <iostream>

typedef struct ElevatorData {
    tm datetime; // datetime data type: https://www.w3schools.com/cpp/cpp_date.asp
    short int floor_number; // 2 bytes long (more than enough)
    bool floor_up_button; // The button to request an elevator to go up *Note: The top and bottom floors will only use one button
    bool floor_down_button; // The button to request an elevator to go down
    //seems were missing the car button press what the hell.
    short int car_to_floor_num;
}e_struct;


#endif //ELEVATORDATATYPES_H
