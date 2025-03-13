#!/bin/bash

# Prompt the user
echo "This test may take up to 45s. Continue? [Y/N]"
read -r choice

# Check the user's input
case "$choice" in
    Y|y)
        echo "Starting the test..."
        # Continue with the rest of the script
        cmake -S . -B build
        cmake --build build
        cd build || exit
        ctest
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