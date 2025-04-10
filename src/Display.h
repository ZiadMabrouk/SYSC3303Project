//
// Created by nelspc on 09/04/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include "ElevatorDataTypes.h"
#include "Datagram2.h"

#define RECEIVE_PORT 10000


class Display {
public:
  e_struct receiveData;
  DatagramSocket sendSocket;
  DatagramSocket receiveSocket;

  std::vector<e_struct> elevators;
  int numElevators;

  DatagramSocket& getReceiveSocket();
  DatagramSocket& getSendSocket();

  explicit Display(int num_elevators);

  e_struct wait_and_receive_with_ack(std::string name, DatagramSocket& iReceiveSocket, DatagramSocket& iSendSocket) {
    std::vector<uint8_t> data(sizeof(e_struct));
    DatagramPacket receivePacket(data, data.size());

    try {
      iReceiveSocket.receive(receivePacket);
    } catch (const std::runtime_error& e) {
      exit(1);
    }
    e_struct receivedData = e_struct::deserialize(data.data());
    e_struct sendStruct = receivedData;
    sendStruct.acknowledged = true;
    sendStruct.serialize(data.data()); // compress the struct to bytes

    DatagramPacket sendPacket(data, receivePacket.getLength(),
                                  receivePacket.getAddress(), receivePacket.getPort());
    try {
      iSendSocket.send(sendPacket);  // Send response back to client
    } catch (const std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
      exit(1);
    }
    return receivedData;

  }

  void guiThread();
  void updateThread();
  void run();
};



#endif //DISPLAY_H
