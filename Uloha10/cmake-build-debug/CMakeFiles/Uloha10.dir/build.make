# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Uloha10.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Uloha10.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Uloha10.dir/flags.make

CMakeFiles/Uloha10.dir/main.c.obj: CMakeFiles/Uloha10.dir/flags.make
CMakeFiles/Uloha10.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Uloha10.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Uloha10.dir\main.c.obj -c "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\main.c"

CMakeFiles/Uloha10.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Uloha10.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\main.c" > CMakeFiles\Uloha10.dir\main.c.i

CMakeFiles/Uloha10.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Uloha10.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\main.c" -o CMakeFiles\Uloha10.dir\main.c.s

# Object files for target Uloha10
Uloha10_OBJECTS = \
"CMakeFiles/Uloha10.dir/main.c.obj"

# External object files for target Uloha10
Uloha10_EXTERNAL_OBJECTS =

Uloha10.exe: CMakeFiles/Uloha10.dir/main.c.obj
Uloha10.exe: CMakeFiles/Uloha10.dir/build.make
Uloha10.exe: CMakeFiles/Uloha10.dir/linklibs.rsp
Uloha10.exe: CMakeFiles/Uloha10.dir/objects1.rsp
Uloha10.exe: CMakeFiles/Uloha10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Uloha10.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Uloha10.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Uloha10.dir/build: Uloha10.exe
.PHONY : CMakeFiles/Uloha10.dir/build

CMakeFiles/Uloha10.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Uloha10.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Uloha10.dir/clean

CMakeFiles/Uloha10.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10" "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10" "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\cmake-build-debug" "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\cmake-build-debug" "C:\Users\samue\Documents\Vysoka_Skola\Semester_#4\FYZAKPH\Uloha10\cmake-build-debug\CMakeFiles\Uloha10.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Uloha10.dir/depend

