# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.3.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.3.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Daniel\CLionProjects\SYSC3303Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SYSC3303Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SYSC3303Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SYSC3303Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SYSC3303Project.dir/flags.make

CMakeFiles/SYSC3303Project.dir/src/main.cpp.obj: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/main.cpp.obj: C:/Users/Daniel/CLionProjects/SYSC3303Project/src/main.cpp
CMakeFiles/SYSC3303Project.dir/src/main.cpp.obj: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/main.cpp.obj -MF CMakeFiles\SYSC3303Project.dir\src\main.cpp.obj.d -o CMakeFiles\SYSC3303Project.dir\src\main.cpp.obj -c C:\Users\Daniel\CLionProjects\SYSC3303Project\src\main.cpp

CMakeFiles/SYSC3303Project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Daniel\CLionProjects\SYSC3303Project\src\main.cpp > CMakeFiles\SYSC3303Project.dir\src\main.cpp.i

CMakeFiles/SYSC3303Project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Daniel\CLionProjects\SYSC3303Project\src\main.cpp -o CMakeFiles\SYSC3303Project.dir\src\main.cpp.s

CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.obj: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.obj: C:/Users/Daniel/CLionProjects/SYSC3303Project/src/Elevator.cpp
CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.obj: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.obj -MF CMakeFiles\SYSC3303Project.dir\src\Elevator.cpp.obj.d -o CMakeFiles\SYSC3303Project.dir\src\Elevator.cpp.obj -c C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Elevator.cpp

CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Elevator.cpp > CMakeFiles\SYSC3303Project.dir\src\Elevator.cpp.i

CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Elevator.cpp -o CMakeFiles\SYSC3303Project.dir\src\Elevator.cpp.s

CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.obj: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.obj: C:/Users/Daniel/CLionProjects/SYSC3303Project/src/Scheduler.cpp
CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.obj: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.obj -MF CMakeFiles\SYSC3303Project.dir\src\Scheduler.cpp.obj.d -o CMakeFiles\SYSC3303Project.dir\src\Scheduler.cpp.obj -c C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Scheduler.cpp

CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Scheduler.cpp > CMakeFiles\SYSC3303Project.dir\src\Scheduler.cpp.i

CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Scheduler.cpp -o CMakeFiles\SYSC3303Project.dir\src\Scheduler.cpp.s

CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.obj: CMakeFiles/SYSC3303Project.dir/flags.make
CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.obj: C:/Users/Daniel/CLionProjects/SYSC3303Project/src/Floor.cpp
CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.obj: CMakeFiles/SYSC3303Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.obj -MF CMakeFiles\SYSC3303Project.dir\src\Floor.cpp.obj.d -o CMakeFiles\SYSC3303Project.dir\src\Floor.cpp.obj -c C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Floor.cpp

CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Floor.cpp > CMakeFiles\SYSC3303Project.dir\src\Floor.cpp.i

CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Daniel\CLionProjects\SYSC3303Project\src\Floor.cpp -o CMakeFiles\SYSC3303Project.dir\src\Floor.cpp.s

# Object files for target SYSC3303Project
SYSC3303Project_OBJECTS = \
"CMakeFiles/SYSC3303Project.dir/src/main.cpp.obj" \
"CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.obj" \
"CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.obj" \
"CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.obj"

# External object files for target SYSC3303Project
SYSC3303Project_EXTERNAL_OBJECTS =

SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/src/main.cpp.obj
SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/src/Elevator.cpp.obj
SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/src/Scheduler.cpp.obj
SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/src/Floor.cpp.obj
SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/build.make
SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/linkLibs.rsp
SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/objects1.rsp
SYSC3303Project.exe: CMakeFiles/SYSC3303Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable SYSC3303Project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SYSC3303Project.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SYSC3303Project.dir/build: SYSC3303Project.exe
.PHONY : CMakeFiles/SYSC3303Project.dir/build

CMakeFiles/SYSC3303Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SYSC3303Project.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SYSC3303Project.dir/clean

CMakeFiles/SYSC3303Project.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Daniel\CLionProjects\SYSC3303Project C:\Users\Daniel\CLionProjects\SYSC3303Project C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug C:\Users\Daniel\CLionProjects\SYSC3303Project\cmake-build-debug\CMakeFiles\SYSC3303Project.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SYSC3303Project.dir/depend

