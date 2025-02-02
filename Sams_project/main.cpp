#include <iostream>
#include <thread>
#include "Floor.h"
#include "Scheduler.h"




// Think of how to connect everything in great detail.

// Think of the floor and elevator subsystems as the clients
// the Scheduler is the server.

// FLOOR SUBSYSTEM reads in time, floor/elevator number, and button and each line 
// of input to the SCHEDULER

// ELEVATORS will then make calls to the SCHEDUELER (But how will they do this?)
// and (what do the calls look like) does elevator input need to be provided?
// is the above instruction truly concurrent or is this just bad wording from the project doc

// SCEDULER will reply (presumbly to the eleavators) when there is work to be done

// The ELEVATORS will then send Data (probably positional) to the SCHEDULER which will then
// send it back to FLOOR


// KEEP IN MIND: SCHEDULER is only being used as comm channel from floor to elevator 
// back to floor 

// OBJECTIVE: show the program can read the input file and pass the data back and forth

// UNDERSTAND the groups data structure/

// My code:
// will need to import everybody's files at the top using "" instead of <> double check this
// the main thread should trigger everyone else's files as a thread, its really hard to do more than this to be honest? cuz I have no idea about 
// everyones specific implementations.


int main() {
    Scheduler scheduler;
    Floor floor(scheduler);

    std::thread floor_thread( floor);
    floor_thread.join();

    return 0;
}