# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.11

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ws\server_prokey_newV2.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ws\server_prokey_newV2.2\build

# Include any dependencies generated for this target.
include src/CMakeFiles/display.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/display.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/display.dir/flags.make

src/CMakeFiles/display.dir/HMI.cpp.obj: src/CMakeFiles/display.dir/flags.make
src/CMakeFiles/display.dir/HMI.cpp.obj: src/CMakeFiles/display.dir/includes_CXX.rsp
src/CMakeFiles/display.dir/HMI.cpp.obj: ../src/HMI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ws\server_prokey_newV2.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/display.dir/HMI.cpp.obj"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\display.dir\HMI.cpp.obj -c D:\ws\server_prokey_newV2.2\src\HMI.cpp

src/CMakeFiles/display.dir/HMI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display.dir/HMI.cpp.i"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ws\server_prokey_newV2.2\src\HMI.cpp > CMakeFiles\display.dir\HMI.cpp.i

src/CMakeFiles/display.dir/HMI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display.dir/HMI.cpp.s"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ws\server_prokey_newV2.2\src\HMI.cpp -o CMakeFiles\display.dir\HMI.cpp.s

src/CMakeFiles/display.dir/ctrl.cpp.obj: src/CMakeFiles/display.dir/flags.make
src/CMakeFiles/display.dir/ctrl.cpp.obj: src/CMakeFiles/display.dir/includes_CXX.rsp
src/CMakeFiles/display.dir/ctrl.cpp.obj: ../src/ctrl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ws\server_prokey_newV2.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/display.dir/ctrl.cpp.obj"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\display.dir\ctrl.cpp.obj -c D:\ws\server_prokey_newV2.2\src\ctrl.cpp

src/CMakeFiles/display.dir/ctrl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display.dir/ctrl.cpp.i"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ws\server_prokey_newV2.2\src\ctrl.cpp > CMakeFiles\display.dir\ctrl.cpp.i

src/CMakeFiles/display.dir/ctrl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display.dir/ctrl.cpp.s"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ws\server_prokey_newV2.2\src\ctrl.cpp -o CMakeFiles\display.dir\ctrl.cpp.s

src/CMakeFiles/display.dir/display.cpp.obj: src/CMakeFiles/display.dir/flags.make
src/CMakeFiles/display.dir/display.cpp.obj: src/CMakeFiles/display.dir/includes_CXX.rsp
src/CMakeFiles/display.dir/display.cpp.obj: ../src/display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ws\server_prokey_newV2.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/display.dir/display.cpp.obj"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\display.dir\display.cpp.obj -c D:\ws\server_prokey_newV2.2\src\display.cpp

src/CMakeFiles/display.dir/display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display.dir/display.cpp.i"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ws\server_prokey_newV2.2\src\display.cpp > CMakeFiles\display.dir\display.cpp.i

src/CMakeFiles/display.dir/display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display.dir/display.cpp.s"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ws\server_prokey_newV2.2\src\display.cpp -o CMakeFiles\display.dir\display.cpp.s

src/CMakeFiles/display.dir/key.cpp.obj: src/CMakeFiles/display.dir/flags.make
src/CMakeFiles/display.dir/key.cpp.obj: src/CMakeFiles/display.dir/includes_CXX.rsp
src/CMakeFiles/display.dir/key.cpp.obj: ../src/key.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ws\server_prokey_newV2.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/display.dir/key.cpp.obj"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\display.dir\key.cpp.obj -c D:\ws\server_prokey_newV2.2\src\key.cpp

src/CMakeFiles/display.dir/key.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display.dir/key.cpp.i"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ws\server_prokey_newV2.2\src\key.cpp > CMakeFiles\display.dir\key.cpp.i

src/CMakeFiles/display.dir/key.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display.dir/key.cpp.s"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ws\server_prokey_newV2.2\src\key.cpp -o CMakeFiles\display.dir\key.cpp.s

src/CMakeFiles/display.dir/lock.cpp.obj: src/CMakeFiles/display.dir/flags.make
src/CMakeFiles/display.dir/lock.cpp.obj: src/CMakeFiles/display.dir/includes_CXX.rsp
src/CMakeFiles/display.dir/lock.cpp.obj: ../src/lock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ws\server_prokey_newV2.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/display.dir/lock.cpp.obj"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\display.dir\lock.cpp.obj -c D:\ws\server_prokey_newV2.2\src\lock.cpp

src/CMakeFiles/display.dir/lock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display.dir/lock.cpp.i"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ws\server_prokey_newV2.2\src\lock.cpp > CMakeFiles\display.dir\lock.cpp.i

src/CMakeFiles/display.dir/lock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display.dir/lock.cpp.s"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ws\server_prokey_newV2.2\src\lock.cpp -o CMakeFiles\display.dir\lock.cpp.s

src/CMakeFiles/display.dir/server.cpp.obj: src/CMakeFiles/display.dir/flags.make
src/CMakeFiles/display.dir/server.cpp.obj: src/CMakeFiles/display.dir/includes_CXX.rsp
src/CMakeFiles/display.dir/server.cpp.obj: ../src/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ws\server_prokey_newV2.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/display.dir/server.cpp.obj"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\display.dir\server.cpp.obj -c D:\ws\server_prokey_newV2.2\src\server.cpp

src/CMakeFiles/display.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display.dir/server.cpp.i"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ws\server_prokey_newV2.2\src\server.cpp > CMakeFiles\display.dir\server.cpp.i

src/CMakeFiles/display.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display.dir/server.cpp.s"
	cd /d D:\ws\server_prokey_newV2.2\build\src && D:\MinGW81\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ws\server_prokey_newV2.2\src\server.cpp -o CMakeFiles\display.dir\server.cpp.s

# Object files for target display
display_OBJECTS = \
"CMakeFiles/display.dir/HMI.cpp.obj" \
"CMakeFiles/display.dir/ctrl.cpp.obj" \
"CMakeFiles/display.dir/display.cpp.obj" \
"CMakeFiles/display.dir/key.cpp.obj" \
"CMakeFiles/display.dir/lock.cpp.obj" \
"CMakeFiles/display.dir/server.cpp.obj"

# External object files for target display
display_EXTERNAL_OBJECTS =

src/libdisplay.a: src/CMakeFiles/display.dir/HMI.cpp.obj
src/libdisplay.a: src/CMakeFiles/display.dir/ctrl.cpp.obj
src/libdisplay.a: src/CMakeFiles/display.dir/display.cpp.obj
src/libdisplay.a: src/CMakeFiles/display.dir/key.cpp.obj
src/libdisplay.a: src/CMakeFiles/display.dir/lock.cpp.obj
src/libdisplay.a: src/CMakeFiles/display.dir/server.cpp.obj
src/libdisplay.a: src/CMakeFiles/display.dir/build.make
src/libdisplay.a: src/CMakeFiles/display.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ws\server_prokey_newV2.2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libdisplay.a"
	cd /d D:\ws\server_prokey_newV2.2\build\src && $(CMAKE_COMMAND) -P CMakeFiles\display.dir\cmake_clean_target.cmake
	cd /d D:\ws\server_prokey_newV2.2\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\display.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/display.dir/build: src/libdisplay.a

.PHONY : src/CMakeFiles/display.dir/build

src/CMakeFiles/display.dir/clean:
	cd /d D:\ws\server_prokey_newV2.2\build\src && $(CMAKE_COMMAND) -P CMakeFiles\display.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/display.dir/clean

src/CMakeFiles/display.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ws\server_prokey_newV2.2 D:\ws\server_prokey_newV2.2\src D:\ws\server_prokey_newV2.2\build D:\ws\server_prokey_newV2.2\build\src D:\ws\server_prokey_newV2.2\build\src\CMakeFiles\display.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/display.dir/depend

