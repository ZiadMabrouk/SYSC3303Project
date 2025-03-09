#include "Elevator.h"
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>

// Assuming scheduler will not send me a floor that is lower than my current floor, if I am moving in the UP direction
// Scheduler can only do the above if car direction is set to "IDLE" aka stopped.
// assume all caps will be used for direction data from scheduler.

// 1 thread or 3 lol.
// receiving data socket
// travel there
// send data to scheduler

// What I have left.
// communications
//

// AS OF NOW this only to be called by .addtoQueue Method so make sure to set to this private later
// calculates direction issue with this, is that it needs the floo
void Elevator::calcdirection(short int pfloor) {
    if (current_floor < pfloor)
        direction = UP;

    else if (current_floor > pfloor){
        direction = DOWN;
    }
    // don't account for the case where they are equal, because when travel is called this will get auto detected and accounted for.
    //std::cerr << "Did not pass in floor number, or at least not one that exists in this building!Try again" << std::endl;
}

//Im gonna assume that a floor lower than the elevators current floor, when
void Elevator::addtoQueue(short int floor) {
    std::lock_guard<std::mutex> lock(mtx);
    if (myQueue.empty())
    {// adds floor number, to queue.
        std::cout << " adding floor " << floor << std::endl;
        calcdirection(floor); // sets the direction
        myQueue.push_back(floor); // edge cases
    }
    else if (direction == UP) //this part sorts the vector ascending order(up direction).
    {
        bool inQueue = false;
        for (auto i : myQueue) {
            if (i == floor) {
                inQueue = true;
            }
        }

        if (!inQueue) {
            myQueue.push_back(floor);
            std::sort(myQueue.begin(), myQueue.end());
        }

    }
    else if (direction == DOWN)//this part sorts the vector in descending order(down direction).
    {
        bool inQueue = false;
        for (auto i : myQueue) {
            if (i == floor) {
                inQueue = true;
            }
        }
        if (!inQueue) {
            myQueue.push_back(floor);
            std::sort(myQueue.begin(), myQueue.end(), std::greater<short int>());  // Descending order
        }

    }
    cv.notify_all();  // Notify waiting thread

}

// need to check if myQueue is empty at some point after a pop, so I can change its direction to IDLE
//when traveling to next element.
/**
void Elevator::travel() {
    std::unique_lock<std::mutex> lock(mtx);
    while (myQueue.empty()) cv.wait(lock);
    // this has to be called over and over again, until myQueue is empty. When I implement this functionality, somewhere it will always have to be running.
    while (myQueue.front() != current_floor) {
        std::this_thread::sleep_for(std::chrono::seconds(3));//change this to match excel
        current_floor += 1; // increments the floor by 1. (later worry about hard limit)
        std::cout << "Just passed, floor: " << current_floor << std::endl;

    }// this should also work in the case for calc direction. Do unit testing later.
    std::cout << " Arrived at target floor: " << current_floor << " Opening doors..." << std::endl;
    current_floor = myQueue.front(); //sets the current floor before deleting.
    myQueue.erase(myQueue.begin()); // only erase once you arrive at the floor. Isolate this garbage from the rest so make an doors() method. and call that
    //could have iterator function change the direction state to idle, give myQueue is empty.
    if (myQueue.empty()) {
        std::cout << "Elevator Queue is empty, direction is now IDLE" << std::endl;
        direction = IDLE;
        return;
    }
    cv.notify_all();  // Notify waiting thread

}
**/

// prints queue
void Elevator::printQueue() {
    for (int num: myQueue) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// method so that I can print the direction now that it's enum.
std::string Elevator::stringDirection(Direction direction) {
    switch (direction) {
        case UP: return "UP";
        case DOWN: return "DOWN";
        case IDLE: return "IDLE";
        default: return "UNKNOWN";
    }
}

// this thread will communicate will be receiving from scheduler.
void Elevator::receiverThread() {
    // does the name for receiving matter, when elevator is receiving can't it just be sheduler?
    // have ziad check, my sockets, becuase what I did was scuffed.
    while (true) { // may have to consider removing some of this logic into mainThread instead.
        received_e_struct_ = wait_and_receive_with_ack("Elevator", receiveSocket, sendSocket);
        // now pass it into add_queue, to update myQueue vector
        addtoQueue(received_e_struct_.transmittedFloor); // only thread to call addtoQueue is this one, but myQueue itself will change
        // as other threads
        printQueue();
        std::cout << "Elevator " << ID << "'s current direction is " << stringDirection(direction) << std::endl;

    }
}
/**
void Elevator::mainThread() {
    while (true){
    // this will just have elevator move through floors until reaches it's destination.
        //travel(); // may need to modify to change e_struct elevators data?
        std::lock_guard<std::mutex> lock(mtx2);
        send_e_struct_.elevatorID = ID;
        send_e_struct_.transmittedFloor = current_floor;
        send_e_struct_.direction = direction;
        send_e_struct_.arrived = arrived;
    }
}
**/
/**
void Elevator::senderThread() {
    scheduler_object.send_and_wait_for_ack(threadName, send_e_struct_,PORT + ID, sendSocket, receiveSocket);
}
**/

Elevator::Elevator(int elevatorID) : arrived(false), currentState(new eWaitingForInput), floor_to_go_to(1),  current_floor(1), direction(IDLE) , ID(elevatorID), sendSocket(), receiveSocket(PORT+elevatorID) {
} // initializes the elevator class to object.

void Elevator::operator()() { // defines how the Elevator object acts when called
    //int i = 1;
    //while (true) { // infinite loop
    // elevator_data = scheduler_object.get();
    //
    // std::cout <<"Grab request " << "Floor Number:" << elevator_data.floor_number << std::endl;
    // current_floor = elevator_data.floor_number;
    //
    // elevator_data.arrived = ARRIVED_FOR_PICKUP;
    // std::cout << "Elevator has arrived at Floor Number:" << current_floor << " and the doors are open, waiting for button request"<< std::endl;
    // scheduler_object.put(elevator_data, ELEVATOR_ID); // put elevator_data back into the scheduler object. to update the scheduler on elevators arrival.
    //
    // std::cout << "Elevator is now travelling to: " << elevator_data.car_to_floor_number << std::endl;
    // current_floor = elevator_data.car_to_floor_number;
    // elevator_data.arrived = ARRIVED_FOR_DROPOFF;
    // std::cout << "Elevator has arrived at Floor Number:" << current_floor << " for drop off and the doors are now closed "<< std::endl;
    // scheduler_object.put(elevator_data, ELEVATOR_ID);

    // e_struct that will tell me what to add into my queue.
    //elevator_data = scheduler_object.wait_and_receive_with_ack("elevatorX", receiveSocket, sendSocket);

    //void return type what I am sending the scheduler so my e_struct with my shit, which will just call somet

    //elevator will have positive id and floor will be negative.

    //scheduler_object.send_and_wait_for_ack("elevatorX", elevator_data,5000, sendSocket, receiveSocket);



    //this->addtoQueue(3);
    //std::cout << "elevators current direction is " << direction << std::endl; //Change Direction to a string before passing it into a print
    //travel();
    //this->printQueue();
    //this->addtoQueue(1);
    //this->addtoQueue(16);
    //this->addtoQueue(2);
    //this->printQueue();
    //travel();
    //i--;

    std::thread t1(&Elevator::receiverThread, this);
    handle();


    t1.join();
}

std::vector<short int> Elevator::getQueue() {
    return myQueue;
}

void Elevator::handle() {
    currentState->handle(this);
}

void Elevator::send_and_wait_for_ack(std::string name, e_struct sendingData, int port, DatagramSocket &iReceiveSocket, DatagramSocket &iSendSocket) {
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
}

e_struct Elevator::wait_and_receive_with_ack(std::string name, DatagramSocket& iReceiveSocket, DatagramSocket& iSendSocket) {
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


void eWaitingForInput::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Waiting for input / IDLE" << std::endl;

    if (true) { // lock scope
        std::unique_lock<std::mutex> lock(context->mtx);
        while (context->myQueue.empty()) context->cv.wait(lock);
        context->printQueue();
        context->floor_to_go_to = context->myQueue.front();
    }
    std::cout << "Elevator " << context->ID << ": Received Request" << std::endl;
    context->setState(new ProcessRequest());
    context->handle();
}

void ProcessRequest::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Processed Request" << std::endl;
    context->setState(new CruiseAndWait());
    context->handle();

}

void CruiseAndWait::handle(Elevator* context) {

    std::cout << "Moving..." << std::endl;
    while (context->floor_to_go_to != context->current_floor) {
        std::this_thread::sleep_for(std::chrono::seconds(3));//change this to match excel
        if (true) {
            std::unique_lock<std::mutex> lock(context->mtx);
            std::cout << "Current Direction: " << context->stringDirection(context->direction) << std::endl;
            if (context->direction == UP) {
                context->current_floor += 1; // increments the floor by 1. (later worry about hard limit)
            } else if (context->direction == DOWN) {
                context->current_floor -= 1;
            }// increments the floor by 1. (later worry about hard limit)
        }
        context->send_e_struct_.transmittedFloor = context->current_floor;
        context->send_and_wait_for_ack(context->threadName, context->send_e_struct_,PORT + context->ID, context->sendSocket, context->receiveSocket);

        std::cout <<  "Elevator " << context->ID <<": Just passed, floor " << context->current_floor << std::endl;

        //check if we receive a new request and need to change floor_to_go_to
        int new_state = false;
        if (true) {
            std::unique_lock<std::mutex> lock(context->mtx);
            if (context->myQueue.front() != context->floor_to_go_to) {
                std::cout <<"New input received" << std::endl;
                context->floor_to_go_to = context->myQueue.front();
                new_state = true;
            }
        }
        if (new_state == true) {
            context->setState(new ProcessRequest());
            context->handle();
        }
    }
    if (context->floor_to_go_to == context->current_floor) {
        context->setState(new Stopped());
        context->handle();
    }

}

void Stopped::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Stopped." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    context->setState(new DoorsOpened());
    context->handle();
}

void DoorsOpened::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Doors Opened." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    context->setState(new InformSchedulerOfArrival());
    context->handle();
}

void InformSchedulerOfArrival::handle(Elevator* context) {
    std::cout << "Informing Scheduler of Arrival" << std::endl;


    if (true) {
        std::unique_lock<std::mutex> lock(context->mtx);
        context->send_e_struct_.arrived = true;

        context->myQueue.erase(context->myQueue.begin()); // only erase once you arrive at the floor. Isolate this garbage from the rest so make an doors() method. and call that

        if (context->myQueue.empty()) {
            std::cout << "Elevator Queue is empty, direction is now IDLE" << std::endl;
            context->direction = IDLE;
        }
    }

    context->send_and_wait_for_ack(context->threadName, context->send_e_struct_,PORT + context->ID, context->sendSocket, context->receiveSocket);

    context->setState(new DoorsClosed());
    context->handle();
}

void DoorsClosed::handle(Elevator* context) {
    std::cout << "Elevator " << context->ID << ": Doors Closed." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (true) {
        std::unique_lock<std::mutex> lock(context->mtx);
        context->send_e_struct_.arrived = false;

        if (context->direction == IDLE) {
            context->setState(new eWaitingForInput());
        } else {
            context->floor_to_go_to = context->myQueue.front();
            context->setState(new CruiseAndWait());
        }
    }
    context->handle();
}

int main() {
    Elevator elevator(1);
    elevator.operator()();
}


