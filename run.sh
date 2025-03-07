cd src || exit
g++ *.cpp *.h -o ../builds/main
cd ..
cd builds || exit
chmod +x main
./main