# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /cygdrive/c/Users/Ivang/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Ivang/.CLion2018.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/matam_3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/matam_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matam_3.dir/flags.make

CMakeFiles/matam_3.dir/wet_files/test.cpp.o: CMakeFiles/matam_3.dir/flags.make
CMakeFiles/matam_3.dir/wet_files/test.cpp.o: ../wet_files/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matam_3.dir/wet_files/test.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matam_3.dir/wet_files/test.cpp.o -c /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/wet_files/test.cpp

CMakeFiles/matam_3.dir/wet_files/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matam_3.dir/wet_files/test.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/wet_files/test.cpp > CMakeFiles/matam_3.dir/wet_files/test.cpp.i

CMakeFiles/matam_3.dir/wet_files/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matam_3.dir/wet_files/test.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/wet_files/test.cpp -o CMakeFiles/matam_3.dir/wet_files/test.cpp.s

# Object files for target matam_3
matam_3_OBJECTS = \
"CMakeFiles/matam_3.dir/wet_files/test.cpp.o"

# External object files for target matam_3
matam_3_EXTERNAL_OBJECTS =

matam_3.exe: CMakeFiles/matam_3.dir/wet_files/test.cpp.o
matam_3.exe: CMakeFiles/matam_3.dir/build.make
matam_3.exe: CMakeFiles/matam_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable matam_3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matam_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matam_3.dir/build: matam_3.exe

.PHONY : CMakeFiles/matam_3.dir/build

CMakeFiles/matam_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matam_3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matam_3.dir/clean

CMakeFiles/matam_3.dir/depend:
	cd /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3 /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3 /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/cmake-build-debug /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/cmake-build-debug /cygdrive/c/Users/Ivang/CLionProjects/matam_3/Matam_3/cmake-build-debug/CMakeFiles/matam_3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matam_3.dir/depend

