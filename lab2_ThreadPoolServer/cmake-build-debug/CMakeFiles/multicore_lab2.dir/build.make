# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "/Users/kehan/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/kehan/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kehan/Desktop/multicore_lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kehan/Desktop/multicore_lab2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/multicore_lab2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multicore_lab2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multicore_lab2.dir/flags.make

CMakeFiles/multicore_lab2.dir/httpreq.cc.o: CMakeFiles/multicore_lab2.dir/flags.make
CMakeFiles/multicore_lab2.dir/httpreq.cc.o: ../httpreq.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multicore_lab2.dir/httpreq.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multicore_lab2.dir/httpreq.cc.o -c /Users/kehan/Desktop/multicore_lab2/httpreq.cc

CMakeFiles/multicore_lab2.dir/httpreq.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multicore_lab2.dir/httpreq.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kehan/Desktop/multicore_lab2/httpreq.cc > CMakeFiles/multicore_lab2.dir/httpreq.cc.i

CMakeFiles/multicore_lab2.dir/httpreq.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multicore_lab2.dir/httpreq.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kehan/Desktop/multicore_lab2/httpreq.cc -o CMakeFiles/multicore_lab2.dir/httpreq.cc.s

CMakeFiles/multicore_lab2.dir/httpreq.cc.o.requires:

.PHONY : CMakeFiles/multicore_lab2.dir/httpreq.cc.o.requires

CMakeFiles/multicore_lab2.dir/httpreq.cc.o.provides: CMakeFiles/multicore_lab2.dir/httpreq.cc.o.requires
	$(MAKE) -f CMakeFiles/multicore_lab2.dir/build.make CMakeFiles/multicore_lab2.dir/httpreq.cc.o.provides.build
.PHONY : CMakeFiles/multicore_lab2.dir/httpreq.cc.o.provides

CMakeFiles/multicore_lab2.dir/httpreq.cc.o.provides.build: CMakeFiles/multicore_lab2.dir/httpreq.cc.o


CMakeFiles/multicore_lab2.dir/httpresp.cc.o: CMakeFiles/multicore_lab2.dir/flags.make
CMakeFiles/multicore_lab2.dir/httpresp.cc.o: ../httpresp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/multicore_lab2.dir/httpresp.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multicore_lab2.dir/httpresp.cc.o -c /Users/kehan/Desktop/multicore_lab2/httpresp.cc

CMakeFiles/multicore_lab2.dir/httpresp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multicore_lab2.dir/httpresp.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kehan/Desktop/multicore_lab2/httpresp.cc > CMakeFiles/multicore_lab2.dir/httpresp.cc.i

CMakeFiles/multicore_lab2.dir/httpresp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multicore_lab2.dir/httpresp.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kehan/Desktop/multicore_lab2/httpresp.cc -o CMakeFiles/multicore_lab2.dir/httpresp.cc.s

CMakeFiles/multicore_lab2.dir/httpresp.cc.o.requires:

.PHONY : CMakeFiles/multicore_lab2.dir/httpresp.cc.o.requires

CMakeFiles/multicore_lab2.dir/httpresp.cc.o.provides: CMakeFiles/multicore_lab2.dir/httpresp.cc.o.requires
	$(MAKE) -f CMakeFiles/multicore_lab2.dir/build.make CMakeFiles/multicore_lab2.dir/httpresp.cc.o.provides.build
.PHONY : CMakeFiles/multicore_lab2.dir/httpresp.cc.o.provides

CMakeFiles/multicore_lab2.dir/httpresp.cc.o.provides.build: CMakeFiles/multicore_lab2.dir/httpresp.cc.o


CMakeFiles/multicore_lab2.dir/main.cpp.o: CMakeFiles/multicore_lab2.dir/flags.make
CMakeFiles/multicore_lab2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/multicore_lab2.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multicore_lab2.dir/main.cpp.o -c /Users/kehan/Desktop/multicore_lab2/main.cpp

CMakeFiles/multicore_lab2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multicore_lab2.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kehan/Desktop/multicore_lab2/main.cpp > CMakeFiles/multicore_lab2.dir/main.cpp.i

CMakeFiles/multicore_lab2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multicore_lab2.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kehan/Desktop/multicore_lab2/main.cpp -o CMakeFiles/multicore_lab2.dir/main.cpp.s

CMakeFiles/multicore_lab2.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/multicore_lab2.dir/main.cpp.o.requires

CMakeFiles/multicore_lab2.dir/main.cpp.o.provides: CMakeFiles/multicore_lab2.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/multicore_lab2.dir/build.make CMakeFiles/multicore_lab2.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/multicore_lab2.dir/main.cpp.o.provides

CMakeFiles/multicore_lab2.dir/main.cpp.o.provides.build: CMakeFiles/multicore_lab2.dir/main.cpp.o


CMakeFiles/multicore_lab2.dir/md5.cpp.o: CMakeFiles/multicore_lab2.dir/flags.make
CMakeFiles/multicore_lab2.dir/md5.cpp.o: ../md5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/multicore_lab2.dir/md5.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multicore_lab2.dir/md5.cpp.o -c /Users/kehan/Desktop/multicore_lab2/md5.cpp

CMakeFiles/multicore_lab2.dir/md5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multicore_lab2.dir/md5.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kehan/Desktop/multicore_lab2/md5.cpp > CMakeFiles/multicore_lab2.dir/md5.cpp.i

CMakeFiles/multicore_lab2.dir/md5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multicore_lab2.dir/md5.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kehan/Desktop/multicore_lab2/md5.cpp -o CMakeFiles/multicore_lab2.dir/md5.cpp.s

CMakeFiles/multicore_lab2.dir/md5.cpp.o.requires:

.PHONY : CMakeFiles/multicore_lab2.dir/md5.cpp.o.requires

CMakeFiles/multicore_lab2.dir/md5.cpp.o.provides: CMakeFiles/multicore_lab2.dir/md5.cpp.o.requires
	$(MAKE) -f CMakeFiles/multicore_lab2.dir/build.make CMakeFiles/multicore_lab2.dir/md5.cpp.o.provides.build
.PHONY : CMakeFiles/multicore_lab2.dir/md5.cpp.o.provides

CMakeFiles/multicore_lab2.dir/md5.cpp.o.provides.build: CMakeFiles/multicore_lab2.dir/md5.cpp.o


CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o: CMakeFiles/multicore_lab2.dir/flags.make
CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o: ../ThreadPoolServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o -c /Users/kehan/Desktop/multicore_lab2/ThreadPoolServer.cpp

CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kehan/Desktop/multicore_lab2/ThreadPoolServer.cpp > CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.i

CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kehan/Desktop/multicore_lab2/ThreadPoolServer.cpp -o CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.s

CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.requires:

.PHONY : CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.requires

CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.provides: CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/multicore_lab2.dir/build.make CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.provides.build
.PHONY : CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.provides

CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.provides.build: CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o


CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o: CMakeFiles/multicore_lab2.dir/flags.make
CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o: ../ThreadSafeKVStore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o -c /Users/kehan/Desktop/multicore_lab2/ThreadSafeKVStore.cpp

CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kehan/Desktop/multicore_lab2/ThreadSafeKVStore.cpp > CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.i

CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kehan/Desktop/multicore_lab2/ThreadSafeKVStore.cpp -o CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.s

CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.requires:

.PHONY : CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.requires

CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.provides: CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.requires
	$(MAKE) -f CMakeFiles/multicore_lab2.dir/build.make CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.provides.build
.PHONY : CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.provides

CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.provides.build: CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o


CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o: CMakeFiles/multicore_lab2.dir/flags.make
CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o: ../ThreadSafeListenerQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o -c /Users/kehan/Desktop/multicore_lab2/ThreadSafeListenerQueue.cpp

CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kehan/Desktop/multicore_lab2/ThreadSafeListenerQueue.cpp > CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.i

CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kehan/Desktop/multicore_lab2/ThreadSafeListenerQueue.cpp -o CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.s

CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.requires:

.PHONY : CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.requires

CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.provides: CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.requires
	$(MAKE) -f CMakeFiles/multicore_lab2.dir/build.make CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.provides.build
.PHONY : CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.provides

CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.provides.build: CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o


# Object files for target multicore_lab2
multicore_lab2_OBJECTS = \
"CMakeFiles/multicore_lab2.dir/httpreq.cc.o" \
"CMakeFiles/multicore_lab2.dir/httpresp.cc.o" \
"CMakeFiles/multicore_lab2.dir/main.cpp.o" \
"CMakeFiles/multicore_lab2.dir/md5.cpp.o" \
"CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o" \
"CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o" \
"CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o"

# External object files for target multicore_lab2
multicore_lab2_EXTERNAL_OBJECTS =

multicore_lab2: CMakeFiles/multicore_lab2.dir/httpreq.cc.o
multicore_lab2: CMakeFiles/multicore_lab2.dir/httpresp.cc.o
multicore_lab2: CMakeFiles/multicore_lab2.dir/main.cpp.o
multicore_lab2: CMakeFiles/multicore_lab2.dir/md5.cpp.o
multicore_lab2: CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o
multicore_lab2: CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o
multicore_lab2: CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o
multicore_lab2: CMakeFiles/multicore_lab2.dir/build.make
multicore_lab2: CMakeFiles/multicore_lab2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable multicore_lab2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multicore_lab2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multicore_lab2.dir/build: multicore_lab2

.PHONY : CMakeFiles/multicore_lab2.dir/build

CMakeFiles/multicore_lab2.dir/requires: CMakeFiles/multicore_lab2.dir/httpreq.cc.o.requires
CMakeFiles/multicore_lab2.dir/requires: CMakeFiles/multicore_lab2.dir/httpresp.cc.o.requires
CMakeFiles/multicore_lab2.dir/requires: CMakeFiles/multicore_lab2.dir/main.cpp.o.requires
CMakeFiles/multicore_lab2.dir/requires: CMakeFiles/multicore_lab2.dir/md5.cpp.o.requires
CMakeFiles/multicore_lab2.dir/requires: CMakeFiles/multicore_lab2.dir/ThreadPoolServer.cpp.o.requires
CMakeFiles/multicore_lab2.dir/requires: CMakeFiles/multicore_lab2.dir/ThreadSafeKVStore.cpp.o.requires
CMakeFiles/multicore_lab2.dir/requires: CMakeFiles/multicore_lab2.dir/ThreadSafeListenerQueue.cpp.o.requires

.PHONY : CMakeFiles/multicore_lab2.dir/requires

CMakeFiles/multicore_lab2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multicore_lab2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multicore_lab2.dir/clean

CMakeFiles/multicore_lab2.dir/depend:
	cd /Users/kehan/Desktop/multicore_lab2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kehan/Desktop/multicore_lab2 /Users/kehan/Desktop/multicore_lab2 /Users/kehan/Desktop/multicore_lab2/cmake-build-debug /Users/kehan/Desktop/multicore_lab2/cmake-build-debug /Users/kehan/Desktop/multicore_lab2/cmake-build-debug/CMakeFiles/multicore_lab2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multicore_lab2.dir/depend

