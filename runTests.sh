g++ -DUNIT_TEST -o builds/tests tests/UnitTestCasesForIteration.cpp src/Elevator.cpp src/Scheduler.cpp src/Floor.cpp -I src -pthread
cd builds || exit
chmod +x tests.o
./tests