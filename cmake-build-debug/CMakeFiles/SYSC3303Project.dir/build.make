# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/Clion/CLion-2024.3.3/clion-2024.3.3/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /opt/Clion/CLion-2024.3.3/clion-2024.3.3/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Desktop/SYSC3303Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Desktop/SYSC3303Project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SYSC3303Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SYSC3303Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SYSC3303Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SYSC3303Project.dir/flags.make

CMakeFiles/SYSC3303Project.dir/src/main.cpp.o: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/main.cpp.o: /home/user/Desktop/SYSC3303Project/src/main.cpp
CMakeFiles/SYSC3303Project.dir/src/main.cpp.o: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/Desktop/SYSC3303Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/main.cpp.o -MF CMakeFiles/SYSC3303Project.dir/src/main.cpp.o.d -o CMakeFiles/SYSC3303Project.dir/src/main.cpp.o -c /home/user/Desktop/SYSC3303Project/src/main.cpp

CMakeFiles/SYSC3303Project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/SYSC3303Project/src/main.cpp > CMakeFiles/SYSC3303Project.dir/src/main.cpp.i

CMakeFiles/SYSC3303Project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/SYSC3303Project/src/main.cpp -o CMakeFiles/SYSC3303Project.dir/src/main.cpp.s

CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o: /home/user/Desktop/SYSC3303Project/src/Elevator.cpp
CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/Desktop/SYSC3303Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o -MF CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o.d -o CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o -c /home/user/Desktop/SYSC3303Project/src/Elevator.cpp

CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/SYSC3303Project/src/Elevator.cpp > CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.i

CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/SYSC3303Project/src/Elevator.cpp -o CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.s

CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o: /home/user/Desktop/SYSC3303Project/src/Scheduler.cpp
CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/Desktop/SYSC3303Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o -MF CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o.d -o CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o -c /home/user/Desktop/SYSC3303Project/src/Scheduler.cpp

CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/SYSC3303Project/src/Scheduler.cpp > CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.i

CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/SYSC3303Project/src/Scheduler.cpp -o CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.s

CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o: /home/user/Desktop/SYSC3303Project/src/Floor.cpp
CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/Desktop/SYSC3303Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o -MF CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o.d -o CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o -c /home/user/Desktop/SYSC3303Project/src/Floor.cpp

CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/SYSC3303Project/src/Floor.cpp > CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.i

CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/SYSC3303Project/src/Floor.cpp -o CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.s

# Object files for target SYSC3303Project
SYSC3303Project_OBJECTS = \
"CMakeFiles/SYSC3303Project.dir/src/main.cpp.o" \
"CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o" \
"CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o" \
"CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o"

# External object files for target SYSC3303Project
SYSC3303Project_EXTERNAL_OBJECTS =

SYSC3303Project: CMakeFiles/SYSC3303Project.dir/src/main.cpp.o
SYSC3303Project: CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.o
SYSC3303Project: CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.o
SYSC3303Project: CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.o
SYSC3303Project: CMakeFiles/SYSC3303Project.dir/build.make
SYSC3303Project: CMakeFiles/SYSC3303Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/user/Desktop/SYSC3303Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable SYSC3303Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SYSC3303Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SYSC3303Project.dir/build: SYSC3303Project
.PHONY : CMakeFiles/SYSC3303Project.dir/build

CMakeFiles/SYSC3303Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SYSC3303Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SYSC3303Project.dir/clean

CMakeFiles/SYSC3303Project.dir/depend:
	cd /home/user/Desktop/SYSC3303Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Desktop/SYSC3303Project /home/user/Desktop/SYSC3303Project /home/user/Desktop/SYSC3303Project/cmake-build-debug /home/user/Desktop/SYSC3303Project/cmake-build-debug /home/user/Desktop/SYSC3303Project/cmake-build-debug/CMakeFiles/SYSC3303Project.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SYSC3303Project.dir/depend

