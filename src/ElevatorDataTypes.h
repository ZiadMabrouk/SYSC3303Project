#ifndef ELEVATORDATATYPES_H
#define ELEVATORDATATYPES_H
#include <ctime>
#include <iostream>

struct elevatorData{
    tm datetime; // datetime data type: https://www.w3schools.com/cpp/cpp_date.asp
    short int floor_number; // 2 bytes long (more than enough)
    bool floor_up_button; // The button to request an elevator to go up *Note: The top and bottom floors will only use one button
    bool floor_down_button; // The button to request an elevator to go down

    elevatorData(tm datetime, short int floor_number, bool floor_up_button, bool floor_down_button) :
        datetime(datetime), floor_number(floor_number), floor_up_button(floor_up_button), floor_down_button(floor_down_button) {}

    elevatorData() {}
};


#endif //ELEVATORDATATYPES_H
