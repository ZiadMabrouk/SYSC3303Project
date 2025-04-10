#!/bin/bash

# Prompt the user
echo "This test may take up to 45s. Continue? [Y/N]"
read -r choice

DEFAULT_ELEVATORS=4
DEFAULT_FLOORS=22

NUM_ELEVATORS=${1:-$DEFAULT_ELEVATORS}
NUM_FLOORS=${2:-$DEFAULT_FLOORS}

# Check the user's input
case "$choice" in
    Y|y)
        echo "Enter input filename: "
        read -r choice
        echo "Starting the test..."
        rm -rf build
        # Continue with the rest of the script
        cmake -S . -B build
        cmake --build build
        cd build || exit
        ctest

        gnome-terminal -- bash -c "./UI $NUM_ELEVATORS; exec bash"

        cd src || exit
        gnome-terminal -- bash -c "./Scheduler $NUM_ELEVATORS; exec bash"

        for ((i=1; i<=NUM_ELEVATORS; i++))
        do
          gnome-terminal -- bash -c "./Elevator $i; exec bash"
        done

        gnome-terminal -- bash -c "./Floor $NUM_FLOORS $choice; exec bash"
        ;;
    N|n)
        echo "Test aborted."
        exit 0
        ;;
    *)
        echo "Invalid input. Please enter Y or N."
        exit 1
        ;;
esac