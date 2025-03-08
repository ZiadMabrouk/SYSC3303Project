//
// Created by ziadm on 2025-01-30.
//

#include "Scheduler.h"


Scheduler::Scheduler() :  sendSocket(), receiveSocket(SERVER_PORT), currentState(new WaitingForInput()) {

}

Scheduler::Scheduler(int num_elevators) :  currentState(new WaitingForInput()), numElevators(num_elevators) {

    elevators.resize(numElevators);
    for (int i = 0; i < numElevators; i++) {
        elevators[i].elevatorID = i;
        elevators[i].transmittedFloor = 1;
        elevators[i].direction = IDLE;
    }
}



DatagramSocket &Scheduler::getSendSocket() {
    return sendSocket;
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
    std::cout << "Received Struct - ID: " << receivedData.elevatorID << std::endl;
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
    int elevatorID = context->calculateBestScore(context->receiveData.transmittedFloor, context->receiveData.direction);
    std::cout<<"Calculated"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}

void WaitingForInput::handle(Scheduler *context) {

    std::cout<<"Server: Waiting for input... "<<std::endl;
    //logic

    context->receiveData = context->wait_and_receive_with_ack("Server", context->getReceiveSocket(), context->getSendSocket());




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


int Scheduler::calculateScore(e_struct& elevator, int requestedFloor, Direction requestedDirection) {
    // Base score is absolute distance.
    int score = std::abs(elevator.transmittedFloor - requestedFloor);

    // If elevator is idle, that's the whole score.
    if (elevator.direction == IDLE) {
        return score;
    }

    // If elevator is already heading in the right direction and will pass the requested floor, increase the score.
    if ((elevator.direction == UP && requestedFloor > elevator.transmittedFloor && requestedDirection == UP) || (elevator.direction == DOWN && requestedFloor < elevator.transmittedFloor && requestedDirection == DOWN)) {
        return score * 2;
    }

    // Otherwise the elevator is moving away from the requested floor, or it's moving in the wrong direction
    return score / 2;
}

// Determines the elevator with the best(biggest) score and returns its index.
int Scheduler::calculateBestScore(int requestedFloor, Direction requestedDirection) {

    int bestElevatorIndex = 0;
    int bestScore = calculateScore(elevators[0], requestedFloor, requestedDirection);

    for (int i = 1; i < numElevators; i++) {
        int score = calculateScore(elevators[i], requestedFloor, requestedDirection);
        if (score > bestScore) {
            bestScore = score;
            bestElevatorIndex = i;
        }
    }

    return bestElevatorIndex;
}












void Scheduler::operator()() {
    handle();
}

