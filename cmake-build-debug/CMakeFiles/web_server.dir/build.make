# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sjhuang/Documents/projects/web_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sjhuang/Documents/projects/web_server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/web_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/web_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/web_server.dir/flags.make

CMakeFiles/web_server.dir/main.cpp.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sjhuang/Documents/projects/web_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/web_server.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server.dir/main.cpp.o -c /Users/sjhuang/Documents/projects/web_server/main.cpp

CMakeFiles/web_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sjhuang/Documents/projects/web_server/main.cpp > CMakeFiles/web_server.dir/main.cpp.i

CMakeFiles/web_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sjhuang/Documents/projects/web_server/main.cpp -o CMakeFiles/web_server.dir/main.cpp.s

CMakeFiles/web_server.dir/web_server.cpp.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/web_server.cpp.o: ../web_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sjhuang/Documents/projects/web_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/web_server.dir/web_server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server.dir/web_server.cpp.o -c /Users/sjhuang/Documents/projects/web_server/web_server.cpp

CMakeFiles/web_server.dir/web_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/web_server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sjhuang/Documents/projects/web_server/web_server.cpp > CMakeFiles/web_server.dir/web_server.cpp.i

CMakeFiles/web_server.dir/web_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/web_server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sjhuang/Documents/projects/web_server/web_server.cpp -o CMakeFiles/web_server.dir/web_server.cpp.s

CMakeFiles/web_server.dir/http/httpd.cpp.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/http/httpd.cpp.o: ../http/httpd.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sjhuang/Documents/projects/web_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/web_server.dir/http/httpd.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server.dir/http/httpd.cpp.o -c /Users/sjhuang/Documents/projects/web_server/http/httpd.cpp

CMakeFiles/web_server.dir/http/httpd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/http/httpd.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sjhuang/Documents/projects/web_server/http/httpd.cpp > CMakeFiles/web_server.dir/http/httpd.cpp.i

CMakeFiles/web_server.dir/http/httpd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/http/httpd.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sjhuang/Documents/projects/web_server/http/httpd.cpp -o CMakeFiles/web_server.dir/http/httpd.cpp.s

CMakeFiles/web_server.dir/event/event_handle.cpp.o: CMakeFiles/web_server.dir/flags.make
CMakeFiles/web_server.dir/event/event_handle.cpp.o: ../event/event_handle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sjhuang/Documents/projects/web_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/web_server.dir/event/event_handle.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/web_server.dir/event/event_handle.cpp.o -c /Users/sjhuang/Documents/projects/web_server/event/event_handle.cpp

CMakeFiles/web_server.dir/event/event_handle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/web_server.dir/event/event_handle.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sjhuang/Documents/projects/web_server/event/event_handle.cpp > CMakeFiles/web_server.dir/event/event_handle.cpp.i

CMakeFiles/web_server.dir/event/event_handle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/web_server.dir/event/event_handle.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sjhuang/Documents/projects/web_server/event/event_handle.cpp -o CMakeFiles/web_server.dir/event/event_handle.cpp.s

# Object files for target web_server
web_server_OBJECTS = \
"CMakeFiles/web_server.dir/main.cpp.o" \
"CMakeFiles/web_server.dir/web_server.cpp.o" \
"CMakeFiles/web_server.dir/http/httpd.cpp.o" \
"CMakeFiles/web_server.dir/event/event_handle.cpp.o"

# External object files for target web_server
web_server_EXTERNAL_OBJECTS =

web_server: CMakeFiles/web_server.dir/main.cpp.o
web_server: CMakeFiles/web_server.dir/web_server.cpp.o
web_server: CMakeFiles/web_server.dir/http/httpd.cpp.o
web_server: CMakeFiles/web_server.dir/event/event_handle.cpp.o
web_server: CMakeFiles/web_server.dir/build.make
web_server: CMakeFiles/web_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sjhuang/Documents/projects/web_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable web_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/web_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/web_server.dir/build: web_server

.PHONY : CMakeFiles/web_server.dir/build

CMakeFiles/web_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/web_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/web_server.dir/clean

CMakeFiles/web_server.dir/depend:
	cd /Users/sjhuang/Documents/projects/web_server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sjhuang/Documents/projects/web_server /Users/sjhuang/Documents/projects/web_server /Users/sjhuang/Documents/projects/web_server/cmake-build-debug /Users/sjhuang/Documents/projects/web_server/cmake-build-debug /Users/sjhuang/Documents/projects/web_server/cmake-build-debug/CMakeFiles/web_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/web_server.dir/depend

