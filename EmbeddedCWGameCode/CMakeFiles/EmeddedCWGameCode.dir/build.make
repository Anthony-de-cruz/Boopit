# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/toby/Programming/C/EmbeddedCWGameCode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/toby/Programming/C/EmbeddedCWGameCode

# Include any dependencies generated for this target.
include CMakeFiles/EmeddedCWGameCode.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/EmeddedCWGameCode.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/EmeddedCWGameCode.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EmeddedCWGameCode.dir/flags.make

CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o: CMakeFiles/EmeddedCWGameCode.dir/flags.make
CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o: src/main.c
CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o: CMakeFiles/EmeddedCWGameCode.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/toby/Programming/C/EmbeddedCWGameCode/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o -MF CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o.d -o CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o -c /home/toby/Programming/C/EmbeddedCWGameCode/src/main.c

CMakeFiles/EmeddedCWGameCode.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/EmeddedCWGameCode.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/toby/Programming/C/EmbeddedCWGameCode/src/main.c > CMakeFiles/EmeddedCWGameCode.dir/src/main.c.i

CMakeFiles/EmeddedCWGameCode.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/EmeddedCWGameCode.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/toby/Programming/C/EmbeddedCWGameCode/src/main.c -o CMakeFiles/EmeddedCWGameCode.dir/src/main.c.s

CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o: CMakeFiles/EmeddedCWGameCode.dir/flags.make
CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o: src/Game.c
CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o: CMakeFiles/EmeddedCWGameCode.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/toby/Programming/C/EmbeddedCWGameCode/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o -MF CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o.d -o CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o -c /home/toby/Programming/C/EmbeddedCWGameCode/src/Game.c

CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/toby/Programming/C/EmbeddedCWGameCode/src/Game.c > CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.i

CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/toby/Programming/C/EmbeddedCWGameCode/src/Game.c -o CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.s

# Object files for target EmeddedCWGameCode
EmeddedCWGameCode_OBJECTS = \
"CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o" \
"CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o"

# External object files for target EmeddedCWGameCode
EmeddedCWGameCode_EXTERNAL_OBJECTS =

EmeddedCWGameCode: CMakeFiles/EmeddedCWGameCode.dir/src/main.c.o
EmeddedCWGameCode: CMakeFiles/EmeddedCWGameCode.dir/src/Game.c.o
EmeddedCWGameCode: CMakeFiles/EmeddedCWGameCode.dir/build.make
EmeddedCWGameCode: CMakeFiles/EmeddedCWGameCode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/toby/Programming/C/EmbeddedCWGameCode/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable EmeddedCWGameCode"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EmeddedCWGameCode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EmeddedCWGameCode.dir/build: EmeddedCWGameCode
.PHONY : CMakeFiles/EmeddedCWGameCode.dir/build

CMakeFiles/EmeddedCWGameCode.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EmeddedCWGameCode.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EmeddedCWGameCode.dir/clean

CMakeFiles/EmeddedCWGameCode.dir/depend:
	cd /home/toby/Programming/C/EmbeddedCWGameCode && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/toby/Programming/C/EmbeddedCWGameCode /home/toby/Programming/C/EmbeddedCWGameCode /home/toby/Programming/C/EmbeddedCWGameCode /home/toby/Programming/C/EmbeddedCWGameCode /home/toby/Programming/C/EmbeddedCWGameCode/CMakeFiles/EmeddedCWGameCode.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/EmeddedCWGameCode.dir/depend

