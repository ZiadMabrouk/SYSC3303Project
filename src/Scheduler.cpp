//
// Created by ziadm on 2025-01-30.
//

#include "Scheduler.h"

void Scheduler::startMonitoring() {
    monitoringThread = std::thread(&Scheduler::monitorElevators, this);
    // Detach the thread so that it runs independently of the main thread.
    monitoringThread.detach();
}

void Scheduler::monitorElevators() {
        using namespace std::chrono;
        // Variables to track when the idle state started.
        steady_clock::time_point idleStart;
        bool trackingIdle = false;

        while (true) {
            bool allIdle = false;
            {
                // Lock mutex to safely access the shared vector.
                std::lock_guard<std::mutex> lock(elevatorMutex);
                allIdle = std::all_of(elevators.begin(), elevators.end(),
                                        [](const e_struct &elevator) {
                                            return elevator.direction == Direction::IDLE;});
            }

            auto now = steady_clock::now();
            if (allIdle) {
                if (!trackingIdle) {
                    // Start tracking the idle period.
                    idleStart = now;
                    trackingIdle = true;
                } else {
                    // Check if the condition has held for at least 3 seconds.
                    auto elapsed = duration_cast<seconds>(now - idleStart);
                    if (elapsed.count() >= 5) {
                        std::cout << "Monitoring thread: All elevators have been IDLE for at least 3 seconds. Exiting.\n";
                        e_struct elevator;
                        elevator.direction = Direction::IDLE;
                        send_no_wait("Timer Thread", elevator, FLOOR_PORT, receiveSocket, sendSocket);
                        break;  // Condition satisfied for the required time.
                    }
                }
            } else {
                // Reset idle tracking if condition is broken.
                trackingIdle = false;
            }
            // Sleep briefly to avoid busy waiting.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
Scheduler::Scheduler(int num_elevators) :  sendData(), receiveData(),currentState(new WaitingForInput()), numElevators(num_elevators), sendSocket(),receiveSocket(SERVER_PORT) {

    elevators.resize(numElevators);
    for (int i = 0; i < numElevators; i++) {
        elevators[i].elevatorID = i+1;
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

void Scheduler::handle() {
    currentState->handle(this);
}

void Calculation::handle(Scheduler *context) {
    std::cout<<"Calculating..."<<std::endl;
    int index = context->receiveData.elevatorID;
    context->elevators[index - 1].direction = context->receiveData.direction;
    context->elevators[index - 1].transmittedFloor = context->receiveData.transmittedFloor;
    std::cout<<"Calculated"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}

void WaitingForInput::handle(Scheduler *context) {

    std::cout<<"Server: Waiting for input... "<<std::endl;
    //logic

    context->receiveData = wait_and_receive_with_ack("Server", context->getReceiveSocket(), context->getSendSocket());
    if (context->receiveData.elevatorID < 0) {
        context->setState(new Dispatching());
    } else {
        context->setState(new Calculation());
    }


    std::cout<<"Input received... "<<std::endl;
    context->handle();

    delete this;
}

void Dispatching::handle(Scheduler *context) {
    std::cout<<"Dispatching"<<std::endl;
    int elevatorID = 0;
    if (!context->receiveData.stateTest) {
        //test
        e_struct sendtoElevator;

        if (context->receiveData.elevatorID == -10) {
            sendtoElevator.elevatorID = 1;
            sendtoElevator.direction = BROKEN;
            context->elevators[0].direction = BROKEN;
        } else if (context->receiveData.elevatorID == -20) {
            sendtoElevator.elevatorID = 2;
            sendtoElevator.doorJammed = true;
        } else {
            if (context->receiveData.floor_up_button) {
                elevatorID = context->calculateBestScore(context->receiveData.floor_number, UP);
                sendtoElevator.direction = UP;
            } else {
                elevatorID = context->calculateBestScore(context->receiveData.floor_number, DOWN);
                sendtoElevator.direction = DOWN;
            }

            sendtoElevator.elevatorID = elevatorID+1;
            std::cout << "Elevator ID: " << sendtoElevator.elevatorID << std::endl;
            sendtoElevator.transmittedFloor = context->receiveData.floor_number;
            sendtoElevator.car_to_floor_number = context->receiveData.car_to_floor_number;
        }

        send_and_wait_for_ack("Scheduler", sendtoElevator, PORT+sendtoElevator.elevatorID, context->getReceiveSocket(), context->getSendSocket());

        std::cout<<"Dispatched"<<std::endl;

        context->setState(new WaitingForInput());
        context->handle();
        delete this;
    }

}

void AddingRequestToQueue::handle(Scheduler *context) {
    std::cout<<"Adding request to queue..."<<std::endl;
    std::cout<<"Added to queue"<<std::endl;
    context->setState(new WaitingForInput());
    context->handle();
    delete this;
}


double Scheduler::calculateScore(e_struct &elevator, int requestedFloor, Direction requestedDirection) {
    // Base score is absolute distance.
    double score = std::abs(elevator.transmittedFloor - requestedFloor);

    if (elevator.direction == BROKEN) {
        return 1000000;
    }

    // If elevator is idle times by 10.
    if (elevator.direction == IDLE) {
        return score;
    }

    // If elevator is already heading in the right direction and will pass the requested floor, increase the score.
    if ((elevator.direction == UP && requestedFloor > elevator.transmittedFloor && requestedDirection == UP) || (elevator.direction == DOWN && requestedFloor < elevator.transmittedFloor && requestedDirection == DOWN)) {
        return score / 2;
    }

    return score * 2;
}

// Determines the elevator with the best(biggest) score and returns its index.
int Scheduler::calculateBestScore(int requestedFloor, Direction requestedDirection) {

    int bestElevatorIndex = 0;
    double bestScore = calculateScore(elevators[0], requestedFloor, requestedDirection);
    std::cout<<"Score: "<< bestScore << " ID: " << bestElevatorIndex+1 << std::endl;

    for (int i = 1; i < numElevators; i++) {
        double score = calculateScore(elevators[i], requestedFloor, requestedDirection);
        std::cout<<"Score: "<<score<< " ID: " << i+1 << std::endl;
        if (score < bestScore) {
            bestScore = score;
            bestElevatorIndex = i;
        }
    }
    std::cerr << "Best Score: " << bestElevatorIndex << std::endl;
    return bestElevatorIndex;
}

#ifndef UNIT_TEST
int main(int argc, char* argv[]) {
    Scheduler scheduler(std::atoi(argv[1]));
    scheduler.startMonitoring();
    scheduler.handle();
    return EXIT_FAILURE;
}
#endif

