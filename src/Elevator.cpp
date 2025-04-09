#include "Elevator.h"
#include "ElevatorDataTypes.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>

//TODO:  opens and closes doors time value needs to be changed to simulate live data from excel sheet.


//gets current floor
short int Elevator::getCurrentFloor() {
    return current_floor;
}

void Elevator::setCurrentFloor(short int floor) {
    current_floor = floor;
}

void Elevator::setDirection(Direction set2) {
    direction = set2;
}

//Delete if unused.
Direction Elevator::getDirection() {
    return direction;
}

// returns reference and not a copy of myQueue. if this fails then go the setter function route.
std::map<short int, std::vector<std::string>, std::function<bool(short int, short int)>> &Elevator::getQueue() {
    return schedulerQueue;
}
void ElevatorSubsystem::userQueuePush(int key, int value) {

    std::string dictKey;

    // Determine the suffix based on the comparison between key and value.
    if (value > key)
        dictKey = std::to_string(key) + "UP";
    else if (value < key)
        dictKey = std::to_string(key) + "DOWN";
    else
        // When value equals key, choosing "UP" by default.
            dictKey = std::to_string(key) + "UP";
    auto it = myElevator.userQueue.find(dictKey);
    if (it == myElevator.userQueue.end()) {
        // No entry exists for this key: create a new vector containing the value.
        myElevator.userQueue[dictKey] = std::vector<int>{value};
    } else {
        // Entry exists: add the value if it is not already present.
        auto& vec = it->second;
        if (std::find(vec.begin(), vec.end(), value) == vec.end())
            vec.push_back(value);
    }
}


// Pop operation: For a given key, call addtoQueue() on each element
// in the vector, then remove the key-value pair from the dictionary.
// Returns true if the key was found and processed, false otherwise.
bool ElevatorSubsystem::userQueuePop(int floor, const std::string& direction) {
    std::string key = std::to_string(floor) + direction;
    auto it = myElevator.userQueue.find(key);
    if (it == myElevator.userQueue.end()) {
        // Key not found; handle the error.
        std::cerr << "Key " << key << " not found in UserQueue.\n";
        return false;
    }

    // Call addtoQueue on every value in the vector.
    for (int value : it->second) {
        addtoQueue(static_cast<short int>(value), -1);
    }

    // Erase the key and its associated vector from the dictionary.
    myElevator.userQueue.erase(it);
    std::cout << "Erased floor " << std::endl;
    return true;
}




// AS OF NOW this only to be called by .addtoQueue Method so make sure to set to this private later
// calculates direction issue with this, is that it needs the floo
void ElevatorSubsystem::calcdirection(short int pfloor) {
    if (myElevator.getCurrentFloor() < pfloor) // need to get elevators current floor.
        myElevator.setDirection(UP); // need to be able set elevators directon via ElevatorSubsytsem

    else if (myElevator.getCurrentFloor() > pfloor){
        myElevator.setDirection(DOWN);
    }
    // don't account for the case where they are equal, because when travel is called this will get auto detected and accounted for.
    //std::cerr << "Did not pass in floor number, or at least not one that exists in this building!Try again" << std::endl;
}

// TODO: Test to see if get by refenrence works as expected.
//Im gonna assume that a floor lower than the elevators current floor, when
void ElevatorSubsystem::addtoQueue(short int floor, short int car_to_floor) {

    std::string direction;
    bool empty = myElevator.getQueue().empty();
    if (floor > car_to_floor) {
        direction = "DOWN";
    }
    else if (floor < car_to_floor) {
        direction = "UP";
    }
    auto it = myElevator.schedulerQueue.find(floor);
    if (it == myElevator.schedulerQueue.end()) {
            // No entry exists for this key: create a new vector containing the value.
        if (car_to_floor == -1) {
            myElevator.schedulerQueue[floor] = std::vector<std::string>{};
        }
        else {
            myElevator.schedulerQueue[floor] = std::vector{direction};
        }

    } else if (car_to_floor != -1) {
        // Entry exists: add the value if it is not already present.
        auto& vec = it->second;
        if (std::find(vec.begin(), vec.end(), direction) == vec.end()) {
            vec.push_back(direction);
        }
    }



    if (empty || myElevator.getDirection() == IDLE) {// adds floor number, to queue.
        std::cout << " adding floor " << floor << std::endl;
        calcdirection(floor); // sets the direction
        std::cout << "Current Direction (add to Queue): " << myElevator.getDirection() << std::endl;
        sortMapInPlace(myElevator.schedulerQueue, myElevator.getDirection() == UP);//true means ascending order

    }

    else if (myElevator.getDirection() == UP) //this part sorts the vector ascending order(up direction).
    {
        sortMapInPlace(myElevator.schedulerQueue, true);//true means ascending order
    }
    else if (myElevator.getDirection() == DOWN)//this part sorts the vector in descending order(down direction).
    {
        sortMapInPlace(myElevator.schedulerQueue, false);//false means descending order  // Descending order

    }

}


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
void ElevatorSubsystem::sortMapInPlace(
    std::map<short int, std::vector<std::string>, std::function<bool(short int, short int)>>& m,
    bool ascending)
{
    int current_floor = myElevator.getCurrentFloor();
    // Create a new map using the new comparator.
    auto comp = [ascending, current_floor](short int a, short int b) {
        if (ascending) {
            bool aGroup1 = (a > current_floor);
            bool bGroup1 = (b > current_floor);
            // If the keys belong to different groups, the one in group1 comes first.
            if (aGroup1 != bGroup1) {
                return aGroup1 && !bGroup1;
            }
            // If both are in the same group, sort normally (ascending).
            return a < b;
        } else {
            // Descending case.
            bool aGroup1 = (a < current_floor);
            bool bGroup1 = (b < current_floor);
            // If the keys belong to different groups, the one in group1 comes first.
            if (aGroup1 != bGroup1) {
                return aGroup1 && !bGroup1;
            }
            // If both are in the same group, sort normally (descending).
            return a > b;
        }
    };

    // Build a new map with the desired custom comparator.
    std::map<short int, std::vector<std::string>,
             std::function<bool(short int, short int)>> newMap(comp);

    // Insert all elements from the original schedulerQueue into the new map.
    for (const auto& kv : myElevator.getQueue()) {
        newMap.insert(kv);
    }

    // Swap the new map with the original so that schedulerQueue now uses the new order.
    myElevator.getQueue().swap(newMap);
}



// prints queue
void Elevator::printQueue() {
    std::cout << "Map keys:" << std::endl;
    for (const auto& entry : schedulerQueue) {
        std::cout << entry.first << " ";
    }
    std::cout << std::endl;
}

// method so that I can print the direction now that it's enum.
std::string Elevator::stringDirection(Direction direction) {
    switch (direction) {
        case UP: return "UP";
        case DOWN: return "DOWN";
        case IDLE: return "IDLE";
        case BROKEN: return "BROKEN";
        default: return "UNKNOWN";
    }
}

// should work.
// this thread will communicate will be receiving from scheduler.
void ElevatorSubsystem::receiverThread() {
    // does the name for receiving matter, when elevator is receiving can't it just be sheduler?
    // have ziad check, my sockets, becuase what I did was scuffed.
    while (true) { // may have to consider removing some of this logic into mainThread instead.
        // now pass it into add_queue, to update myQueue vector
        // TODO: Consider changing Elevator to ElevatorSubystem if needed.

        received_e_struct_ = wait_and_receive_with_ack("Elevator", receiveSocket, sendSocket);

        if (received_e_struct_.direction == BROKEN) {
            addtoQueue(0, 1);
            myElevator.setDirection(BROKEN);
        }

        if (received_e_struct_.doorJammed) {
            doorsJammed = true;
            // continue;
        }

        std::unique_lock<std::mutex> lock(mtx);

        addtoQueue(received_e_struct_.transmittedFloor, received_e_struct_.car_to_floor_number); // only thread to call addtoQueue is this one, but myQueue itself will change
        userQueuePush(received_e_struct_.transmittedFloor, received_e_struct_.car_to_floor_number);
        // as other threads
        myElevator.printQueue();
        // addtoQueue(received_e_struct_.car_to_floor_number);
        // myElevator.printQueue();
        std::cout << "Elevator " << programID << "'s current direction is " << myElevator.stringDirection(myElevator.getDirection()) << std::endl;
        //std::this_thread::
        cv.notify_all();
    }
}



// make sure to pass the now Elevator Substystem programID as elevatorID
Elevator::Elevator(int elevatorID) : arrived(false), floor_to_go_to(1),  current_floor(1), direction(IDLE) , ID(elevatorID), user_direction(""), schedulerQueue(), userQueue(), destinationFloor(1) {
} // initializes the elevator class to object.

//TODO: Define the constructor for ElevatorSubsystem.
// may not need programID member.
ElevatorSubsystem::ElevatorSubsystem(int elevatorID) : myElevator(elevatorID) , programID(elevatorID),currentState(new eWaitingForInput()), sendSocket(), receiveSocket(PORT+elevatorID){
    sortMapInPlace(myElevator.schedulerQueue, true);
}
void ElevatorSubsystem::deleteEntry(std::map<short int, std::vector<std::string>,
              std::function<bool(short int, short int)>>& schedulerQueue, int key) {
    // Find the key in the map
    auto it = schedulerQueue.find(static_cast<short int>(key));
    if (it == schedulerQueue.end()) {
        std::cerr << "Key " << key << " not found in schedulerQueue." << std::endl;
        return;
    }

    // If the vector has more than one element, remove the first element.
    if (it->second.size() > 1) {
        it->second.erase(it->second.begin());
        std::cout << "Removed the first element from key " << key << "." << std::endl;
    } else {
        // Otherwise, remove the entire key-value pair.
        schedulerQueue.erase(it);
        std::cout << "Removed key " << key << " entirely from schedulerQueue." << std::endl;
    }
}

void ElevatorSubsystem::operator()() {
    std::thread t1(&ElevatorSubsystem::receiverThread, this);
    handle(); // check that this works as expected.
    t1.join();
}
std::pair<short int, std::string> ElevatorSubsystem::front(const std::map<short int, std::vector<std::string>, std::function<bool(short int, short int)>>& m) {
    if (m.empty()) {
        throw std::runtime_error("Error: The map is empty.");
    }

    // Get the first key-value pair (the map is ordered).
    auto iter = m.begin();
    std::string tmp;
    if (iter->second.empty()) {
        tmp = "";
    } else {
        tmp = iter->second.front();
    }

    // Return the key and the first value from the associated vector.
    return std::make_pair(iter->first, tmp);
}
void ElevatorSubsystem::handle() {
    currentState->handle(this);
}

void eWaitingForInput::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Waiting for input / IDLE. Opening Doors" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Elevator " << context->programID << ": Doors Open" << std::endl;
    if (true) { // lock scope
        std::unique_lock<std::mutex> lock(context->mtx);

        while (context->myElevator.getQueue().empty()) context->cv.wait(lock);
        std::cout << "Acquired Mutex" << std::endl;
        if (context->myElevator.getDirection() == BROKEN) {
          context->setState(new BrokenState());
          context->handle();
        }
        context->myElevator.printQueue();
        //review this line. was confused about it before.
        auto floor_and_direction = context->front(context->myElevator.getQueue());
        std::cout << "Floor to go to: " << floor_and_direction.first << std::endl;
        std::cout << "User Direction: " << floor_and_direction.second << std::endl;
        context->myElevator.floor_to_go_to = floor_and_direction.first;
        context->myElevator.user_direction = floor_and_direction.second;

    }
    std::cout << "Elevator " << context->programID << ": Received Request" << std::endl;
    context->setState(new ProcessRequest());
    context->handle();
}

void ProcessRequest::handle(ElevatorSubsystem* context) {
    if (!context->stateTest) {
        std::cout << "Elevator " << context->programID << ": Processed Request" << std::endl;
        context->setState(new CruiseAndWait());
        context->handle();
    }
}
//DOUBLE CHECK FLOOR_TO_GO_TO

void CruiseAndWait::handle(ElevatorSubsystem* context) {
    //Review the context swith changes.
    std::cout << "Moving..." << std::endl;
    std::cout << "Floor to go to: " << context->myElevator.floor_to_go_to << std::endl;
    while (context->myElevator.floor_to_go_to != context->myElevator.getCurrentFloor()) {
        std::this_thread::sleep_for(std::chrono::seconds(ELEVATOR_TIME));//change this to match excel
        if (true) {
            std::unique_lock<std::mutex> lock(context->mtx);
            std::cout << "Current Direction: " << context->myElevator.stringDirection(context->myElevator.getDirection()) << std::endl;
            if (context->myElevator.getDirection() == UP) {
                context->myElevator.setCurrentFloor(context->myElevator.getCurrentFloor()+ 1); // Check that this works properly. increments the floor by 1. (later worry about hard limit)
            } else if (context->myElevator.getDirection()== DOWN) {
                context->myElevator.setCurrentFloor(context->myElevator.getCurrentFloor()-1);
            }// increments the floor by 1. (later worry about hard limit)
        }
        context->send_e_struct_.elevatorID = context->programID;
        context->send_e_struct_.transmittedFloor = context->myElevator.getCurrentFloor();
        context->send_e_struct_.direction = context->myElevator.getDirection();
        send_and_wait_for_ack(context->threadName, context->send_e_struct_,PORT, context->receiveSocket, context->sendSocket);

        std::cout <<  "Elevator " << context->programID <<": Just passed, floor " << context->myElevator.getCurrentFloor() << std::endl;

        //check if we receive a new request and need to change floor_to_go_to
        int new_state = false;
        if (true) {
            std::unique_lock<std::mutex> lock(context->mtx);
            if (context->front(context->myElevator.getQueue()).first != context->myElevator.floor_to_go_to
                ||context->front(context->myElevator.getQueue()).second != context->myElevator.user_direction ) {
                std::cout <<"New input received" << std::endl;
                new_state = true;
            }
        }
        if (new_state == true) {
            context->setState(new ProcessRequest());
            auto floor_and_direction = context->front(context->myElevator.getQueue());
            std::cout << "Floor to go to: " << floor_and_direction.first << std::endl;
            std::cout << "User Direction: " << floor_and_direction.second << std::endl;
            context->myElevator.floor_to_go_to = floor_and_direction.first;
            context->myElevator.user_direction = floor_and_direction.second;
            context->handle();
        }
    }
    if (context->myElevator.floor_to_go_to == context->myElevator.getCurrentFloor()) {
        context->setState(new Stopped());
        context->handle();
    }

}

void Stopped::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Stopped." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // remove the floor we just arrived at

    if (true) {
        std::unique_lock<std::mutex> lock(context->mtx);
        context->deleteEntry(context->myElevator.getQueue(), context->myElevator.getCurrentFloor());
        context->myElevator.setDirection(IDLE);
        if (context->myElevator.user_direction.empty() && context->myElevator.getQueue().empty()) {
            std::cout << "Elevator " << context->programID << ": Done servicing queue" << std::endl;
        } else {
            std::cout << "adding to user queue."<< std::endl;
            // add all the user button requets into the queue

            if (!context->myElevator.user_direction.empty()) { // If we were picking up passengers
                context->userQueuePop(context->myElevator.getCurrentFloor(), context->myElevator.user_direction);
            }
            else {
                context->calcdirection(context->front(context->myElevator.getQueue()).first);
                std::cout << "Current Direction (stopped state): " << context->myElevator.getDirection() << std::endl;
                context->sortMapInPlace(context->myElevator.getQueue(), context->myElevator.getDirection() == UP);
            }
            auto pair = context->front(context->myElevator.getQueue());
            std::cout << "used front."<< std::endl;
            if (!pair.second.empty()) { // If we are picking up passengers
                context->myElevator.user_direction = pair.second;
            }
            else { //dropping off passengers
                context->myElevator.user_direction = "";
            }
            context->myElevator.floor_to_go_to = pair.first;
            context->myElevator.printQueue();
        }
    }


    if (context->doorsJammed) {
      context->setState(new JammedState());
    } else {
      context->setState(new DoorsOpened());
    }
    context->handle();
}

void DoorsOpened::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Doors Opened." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    context->setState(new InformSchedulerOfArrival());
    context->handle();
}

void InformSchedulerOfArrival::handle(ElevatorSubsystem* context) {
    std::cout << "Informing Scheduler of Arrival" << std::endl;


    if (true) {
        std::unique_lock<std::mutex> lock(context->mtx);
        context->send_e_struct_.arrived = true;


        if (context->myElevator.getQueue().empty()) {
            std::cout << "Elevator Queue is empty, direction is now IDLE" << std::endl;
            context->myElevator.setDirection(IDLE);
        }
    }
    send_and_wait_for_ack(context->threadName, context->send_e_struct_,PORT, context->receiveSocket, context->sendSocket);

    context->setState(new DoorsClosed());
    context->handle();
}

void DoorsClosed::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Doors Closed." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (true) {
        std::unique_lock<std::mutex> lock(context->mtx);
        context->send_e_struct_.arrived = false;

        if (context->myElevator.getDirection() == IDLE) {
            context->setState(new eWaitingForInput());
        } else {
            // context->myElevator.floor_to_go_to = context->myElevator.getQueue().front();
            context->setState(new CruiseAndWait());
        }
    }
    context->handle();
}

void BrokenState::handle(ElevatorSubsystem* context) {
    std::cout << "Elevator " << context->programID << ": Stuck Between Floors." << std::endl; // <--- START HERE FOR NEXT ITERATION
    while (1){}
}

void JammedState::handle(ElevatorSubsystem* context) {
    std::cout << "Doors Jammed.... Initated Fixed Doors Routine." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    context->doorsJammed = false;
    std::cout << "Doors have been fixed!!" << std::endl;
    context->setState(new DoorsOpened());
    context->handle();
}

//
#ifndef UNIT_TEST
int main(int argc, char* argv[]) {
    ElevatorSubsystem elevator_subsystem(std::atoi(argv[1]));
    elevator_subsystem.operator()();
}
#endif


