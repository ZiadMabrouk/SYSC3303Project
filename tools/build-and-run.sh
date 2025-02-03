cd ..
cd src
g++ *.cpp *.h -o ../builds/main.o
cd .. 
cd builds
chmod +x main.o
./main.o