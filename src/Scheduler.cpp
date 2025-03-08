//
// Created by ziadm on 2025-01-30.
//

#include "Scheduler.h"


Scheduler::Scheduler() : readfds(), timeout(), sendSocket(), receiveSocket(SERVER_PORT), currentState(new WaitingForInput()) {
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
}

fd_set &Scheduler::getReadfds() {
    return readfds;

}

DatagramSocket &Scheduler::getSendSocket() {
    return sendSocket;
}

struct timeval &Scheduler::getTimeout() {
    return timeout;
}

DatagramSocket& Scheduler::getReceiveSocket() {
    return receiveSocket;
}


e_struct Scheduler::wait_and_receive_with_ack(std::string name, DatagramSocket& iReceiveSocket, DatagramSocket& iSendSocket) {
    std::vector<uint8_t> data(sizeof(e_struct));
    DatagramPacket receivePacket(data, data.size());

    std::cout << name << ": Waiting for Packet." << std::endl;

    try {
        std::cout << "Waiting..." << std::endl;
        iReceiveSocket.receive(receivePacket);
    } catch (const std::runtime_error& e) {
        std::cerr << "IO Exception: Receive Socket Timed Out.\n" << e.what() << std::endl;
        exit(1);
    }

    std::cout << name << ": Packet received:\n";
    std::cout << "From host: " << receivePacket.getAddressAsString() << std::endl;
    std::cout << "Host port: " << receivePacket.getPort() << std::endl;

    // Deserialize received struct
    e_struct receivedData = e_struct::deserialize(data.data());
    std::cout << "Received Struct - ID: " << receivedData.id << std::endl;
    /**
     *Here you can use receivedData.(value) to access a member of the e_struct passed)
     *
     **/
    //Uncomment if there are timing issues
    //std::this_thread::sleep_for(std::chrono::seconds());

    e_struct sendStruct = receivedData;
    sendStruct.acknowledged = true;
    sendStruct.serialize(data.data()); // compress the struct to bytes

    DatagramPacket sendPacket(data, receivePacket.getLength(),
                                  receivePacket.getAddress(), receivePacket.getPort());

    std::cout << name << "Sending acknowledgement back to client...\n";
    try {
        iSendSocket.send(sendPacket);  // Send response back to client
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }




    return receivedData;

}



void Scheduler::handle() {
    currentState->handle(this);
}



void Calculation::handle(Scheduler *context) {
    std::cout<<"Calculating..."<<std::endl;
    std::cout<<"Calculated"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}

void WaitingForInput::handle(Scheduler *context) {

    std::cout<<"Server: Waiting for input... "<<std::endl;
    //logic

    context->receivedData = context->wait_and_receive_with_ack("Server", context->getReceiveSocket(), context->getSendSocket());

    while (true) {
        FD_ZERO(&context->getReadfds());
        FD_SET(context->getReceiveSocket().socket_fd, &context->getReadfds());

        int activity = select(context->getReceiveSocket().socket_fd +1, &context->getReadfds(), NULL, NULL, &context->getTimeout());

        if (activity <0) {
            std::cerr << "Erro in selct()" <<std::endl;
            exit(1);
        }

        else if (activity == 0) {
            std::cerr << "Server timeout()" <<std::endl;
        }

    }


    std::cout<<"Input received... "<<std::endl;
    context->setState(new Dispatching());
    context->handle();

    delete this;
}

void Dispatching::handle(Scheduler *context) {
    std::cout<<"Dispatching"<<std::endl;
    //logic
    std::cout<<"Dispatched"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}

void AddingRequestToQueue::handle(Scheduler *context) {
    std::cout<<"Adding request to queue..."<<std::endl;
    std::cout<<"Added to queue"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}





void Scheduler::operator()() {
    handle();
}



