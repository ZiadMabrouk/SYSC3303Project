Team: Group 2
Members: Daniel Y, Ziad M, Sam A, Jinan K

Setup Instructions:

1. Unzip folder. (Hopefully you have already done this)

2. cd into SYSC3303Project.

3. To run just run ./run.sh {number of elevators} {number of floors} in the terminal. (make sure that Elevator.o, Floor.o and Scheduler.o are found in the /builds directory)
    Ex: ./run.sh 3 22
    *If there are permission errors make sure to run "chmod +x ./run.sh"*

If you need to change the input file, the file string is located in line 22 of Floor.cpp and can be changed as needed.

File Locations:

UML diagrams are found in the /UML directory.
Code for this iteration is found in the /src directory.
Test file is found in the tests directory. (run ./runCatch2.sh to see it in action)
if there are permission errors make sure to run "chmod +x ./runCatch2.sh"

Fault Injections in the Input file:
The input file is found in data/tests/SamTestCase.txt
Floor Timer Fault error is triggered by 'Elevator Breaks Down'.
Door not Closed Fault is triggered by 'Doors Stuck'. The doors are jammed for a total of 5 seconds before going back to normal.

Contributions (Iteration 5):
Daniel - Made Floor more configurable, Error Faults, Interfacing
Ziad - Adjusting Elevator Doors, Test Cases, Interfacing
Sami - Error Faults, Elevator Subsystem, Interfacing
Jinan - Timing Diagram
