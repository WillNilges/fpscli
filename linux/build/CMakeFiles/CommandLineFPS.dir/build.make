# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/wilnil/fpscli/linux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wilnil/fpscli/linux/build

# Include any dependencies generated for this target.
include CMakeFiles/CommandLineFPS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CommandLineFPS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CommandLineFPS.dir/flags.make

CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.o: CMakeFiles/CommandLineFPS.dir/flags.make
CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.o: ../CommandLineFPS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wilnil/fpscli/linux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.o -c /home/wilnil/fpscli/linux/CommandLineFPS.cpp

CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wilnil/fpscli/linux/CommandLineFPS.cpp > CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.i

CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wilnil/fpscli/linux/CommandLineFPS.cpp -o CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.s

# Object files for target CommandLineFPS
CommandLineFPS_OBJECTS = \
"CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.o"

# External object files for target CommandLineFPS
CommandLineFPS_EXTERNAL_OBJECTS =

CommandLineFPS: CMakeFiles/CommandLineFPS.dir/CommandLineFPS.cpp.o
CommandLineFPS: CMakeFiles/CommandLineFPS.dir/build.make
CommandLineFPS: /usr/lib64/libncursesw.so
CommandLineFPS: /usr/lib64/libform.so
CommandLineFPS: CMakeFiles/CommandLineFPS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wilnil/fpscli/linux/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CommandLineFPS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CommandLineFPS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CommandLineFPS.dir/build: CommandLineFPS

.PHONY : CMakeFiles/CommandLineFPS.dir/build

CMakeFiles/CommandLineFPS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CommandLineFPS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CommandLineFPS.dir/clean

CMakeFiles/CommandLineFPS.dir/depend:
	cd /home/wilnil/fpscli/linux/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wilnil/fpscli/linux /home/wilnil/fpscli/linux /home/wilnil/fpscli/linux/build /home/wilnil/fpscli/linux/build /home/wilnil/fpscli/linux/build/CMakeFiles/CommandLineFPS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CommandLineFPS.dir/depend

