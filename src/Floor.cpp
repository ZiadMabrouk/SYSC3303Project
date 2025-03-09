//
// Created by ziadm on 2025-01-30.
//

#include "Floor.h"
#include <chrono>
#include <thread>

#include <random>
#include "ElevatorDataTypes.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>

Floor::Floor() {

}


void Floor::send_and_wait_for_ack(std::string name, e_struct sendingData, int port, DatagramSocket &iReceiveSocket, DatagramSocket &iSendSocket) {
    std::vector<uint8_t> buffer(sizeof(e_struct));  // Create a buffer for the struct
    sendingData.serialize(buffer.data());


    DatagramPacket sendPacket(buffer, buffer.size(), InetAddress::getLocalHost(), port);

    fd_set readfds;
    struct timeval timeout; // Structure to store timeout duration

    std::vector<uint8_t> ackData(sizeof(e_struct));
    DatagramPacket ackPacket(ackData, ackData.size());

    int retries = 0;  // Counter for retry attempts

    while (retries < MAX_RETRIES) {
        try {
            // Send the message to the server
            std::cout << name << "Sending message to server..." << std::endl;
            iSendSocket.send(sendPacket);
        } catch (const std::runtime_error& e) {
            std::cerr << "Send failed: " << e.what() << std::endl;
            return exit(1); // Exit on send failure
        }
        retries++;
        // Clear and set file descriptor set
        FD_ZERO(&readfds);
        FD_SET(iSendSocket.socket_fd, &readfds);

        // Set timeout duration
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = 0;
        std::cout << name << "Waiting for acknowledgment..." << std::endl;

        int activity = select(iSendSocket.socket_fd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            // Error in select()
            std::cerr << "Error in select()" << std::endl;
            return exit(1);
        } else if (activity == 0) {
            // Timeout expired, no ACK received
            std::cout << name << ": Timeout! No acknowledgment received." << std::endl;
            continue; // Exit loop after timeout
        }

        break;
    }
    if (retries == MAX_RETRIES) {
        std::cout << "Max retries." << std::endl;
        exit(1);
    }
}

// this method reads a line from the input file and converts it into e_struct then invokes put into the scheduler object.
void Floor::readFile() {
    std::ifstream file("../data/tests/SamTestCase.txt");//open the file for reading
    e_struct elevatorData;

    std::string line, token;
    while (std::getline(file, line)) { //read each from file and store into line
        std::stringstream ss(line);

        std::getline(ss, token, ' ');// read from ss(line but converted into stream) and store into token up until the first space.
        elevatorData.datetime = formatTime(token);

        std::getline(ss, token, ' ');
        elevatorData.floor_number = atoi(token.c_str());
        std::cout << "Floor Number: " << elevatorData.floor_number << std::endl;

        std::getline(ss, token, ' ');
        if (token == "Up") {
            elevatorData.floor_up_button = true;
            elevatorData.floor_down_button = false;
        } else if (token == "Down") {
            elevatorData.floor_up_button = false;
            elevatorData.floor_down_button = true;
        }

        std::getline(ss, token, ' ');
        elevatorData.car_to_floor_number = atoi(token.c_str());
        elevatorData.elevatorID = -1;

        send_and_wait_for_ack("Floor", elevatorData, PORT, receiveSocket, sendSocket);
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

tm Floor::formatTime(const std::string& str) {

    tm datetime{};
    datetime.tm_hour = atoi(str.substr(0, 2).c_str());
    datetime.tm_min = atoi(str.substr(3, 2).c_str());
    datetime.tm_sec = atoi(str.substr(6, 2).c_str());

    return datetime;
}
#ifndef UNIT_TEST
// invokes the readFile() method.
int main(int argc, char *argv[]) {
    Floor floor;
    floor.readFile();
}
#endif



