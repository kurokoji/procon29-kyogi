# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion-2018.1.5/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.1.5/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rikuto/Projects/procon29-kyogi/kyon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/kyon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kyon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kyon.dir/flags.make

CMakeFiles/kyon.dir/src/button.cpp.o: CMakeFiles/kyon.dir/flags.make
CMakeFiles/kyon.dir/src/button.cpp.o: ../src/button.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kyon.dir/src/button.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyon.dir/src/button.cpp.o -c /home/rikuto/Projects/procon29-kyogi/kyon/src/button.cpp

CMakeFiles/kyon.dir/src/button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyon.dir/src/button.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rikuto/Projects/procon29-kyogi/kyon/src/button.cpp > CMakeFiles/kyon.dir/src/button.cpp.i

CMakeFiles/kyon.dir/src/button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyon.dir/src/button.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rikuto/Projects/procon29-kyogi/kyon/src/button.cpp -o CMakeFiles/kyon.dir/src/button.cpp.s

CMakeFiles/kyon.dir/src/button.cpp.o.requires:

.PHONY : CMakeFiles/kyon.dir/src/button.cpp.o.requires

CMakeFiles/kyon.dir/src/button.cpp.o.provides: CMakeFiles/kyon.dir/src/button.cpp.o.requires
	$(MAKE) -f CMakeFiles/kyon.dir/build.make CMakeFiles/kyon.dir/src/button.cpp.o.provides.build
.PHONY : CMakeFiles/kyon.dir/src/button.cpp.o.provides

CMakeFiles/kyon.dir/src/button.cpp.o.provides.build: CMakeFiles/kyon.dir/src/button.cpp.o


CMakeFiles/kyon.dir/src/CommandGUI.cpp.o: CMakeFiles/kyon.dir/flags.make
CMakeFiles/kyon.dir/src/CommandGUI.cpp.o: ../src/CommandGUI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/kyon.dir/src/CommandGUI.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyon.dir/src/CommandGUI.cpp.o -c /home/rikuto/Projects/procon29-kyogi/kyon/src/CommandGUI.cpp

CMakeFiles/kyon.dir/src/CommandGUI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyon.dir/src/CommandGUI.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rikuto/Projects/procon29-kyogi/kyon/src/CommandGUI.cpp > CMakeFiles/kyon.dir/src/CommandGUI.cpp.i

CMakeFiles/kyon.dir/src/CommandGUI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyon.dir/src/CommandGUI.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rikuto/Projects/procon29-kyogi/kyon/src/CommandGUI.cpp -o CMakeFiles/kyon.dir/src/CommandGUI.cpp.s

CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.requires:

.PHONY : CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.requires

CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.provides: CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.requires
	$(MAKE) -f CMakeFiles/kyon.dir/build.make CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.provides.build
.PHONY : CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.provides

CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.provides.build: CMakeFiles/kyon.dir/src/CommandGUI.cpp.o


CMakeFiles/kyon.dir/src/Main.cpp.o: CMakeFiles/kyon.dir/flags.make
CMakeFiles/kyon.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/kyon.dir/src/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kyon.dir/src/Main.cpp.o -c /home/rikuto/Projects/procon29-kyogi/kyon/src/Main.cpp

CMakeFiles/kyon.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kyon.dir/src/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rikuto/Projects/procon29-kyogi/kyon/src/Main.cpp > CMakeFiles/kyon.dir/src/Main.cpp.i

CMakeFiles/kyon.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kyon.dir/src/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rikuto/Projects/procon29-kyogi/kyon/src/Main.cpp -o CMakeFiles/kyon.dir/src/Main.cpp.s

CMakeFiles/kyon.dir/src/Main.cpp.o.requires:

.PHONY : CMakeFiles/kyon.dir/src/Main.cpp.o.requires

CMakeFiles/kyon.dir/src/Main.cpp.o.provides: CMakeFiles/kyon.dir/src/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/kyon.dir/build.make CMakeFiles/kyon.dir/src/Main.cpp.o.provides.build
.PHONY : CMakeFiles/kyon.dir/src/Main.cpp.o.provides

CMakeFiles/kyon.dir/src/Main.cpp.o.provides.build: CMakeFiles/kyon.dir/src/Main.cpp.o


# Object files for target kyon
kyon_OBJECTS = \
"CMakeFiles/kyon.dir/src/button.cpp.o" \
"CMakeFiles/kyon.dir/src/CommandGUI.cpp.o" \
"CMakeFiles/kyon.dir/src/Main.cpp.o"

# External object files for target kyon
kyon_EXTERNAL_OBJECTS =

kyon: CMakeFiles/kyon.dir/src/button.cpp.o
kyon: CMakeFiles/kyon.dir/src/CommandGUI.cpp.o
kyon: CMakeFiles/kyon.dir/src/Main.cpp.o
kyon: CMakeFiles/kyon.dir/build.make
kyon: CMakeFiles/kyon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable kyon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kyon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kyon.dir/build: kyon

.PHONY : CMakeFiles/kyon.dir/build

CMakeFiles/kyon.dir/requires: CMakeFiles/kyon.dir/src/button.cpp.o.requires
CMakeFiles/kyon.dir/requires: CMakeFiles/kyon.dir/src/CommandGUI.cpp.o.requires
CMakeFiles/kyon.dir/requires: CMakeFiles/kyon.dir/src/Main.cpp.o.requires

.PHONY : CMakeFiles/kyon.dir/requires

CMakeFiles/kyon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kyon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kyon.dir/clean

CMakeFiles/kyon.dir/depend:
	cd /home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rikuto/Projects/procon29-kyogi/kyon /home/rikuto/Projects/procon29-kyogi/kyon /home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug /home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug /home/rikuto/Projects/procon29-kyogi/kyon/cmake-build-debug/CMakeFiles/kyon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kyon.dir/depend

