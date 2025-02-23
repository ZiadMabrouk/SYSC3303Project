cd tests || exit
g++ ProjectTest.cpp -o ../builds/tests.o
cd ..
cd builds || exit
chmod +x tests.o
./tests.o