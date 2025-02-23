cd src || exit
g++ *.cpp *.h -o ../builds/main.o
cd ..
cd builds || exit
chmod +x main.o
./main.o