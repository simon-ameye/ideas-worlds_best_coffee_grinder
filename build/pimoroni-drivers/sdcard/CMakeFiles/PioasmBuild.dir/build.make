# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/speedhacker/pico/devs/first

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/speedhacker/pico/devs/first/build

# Utility rule file for PioasmBuild.

# Include any custom commands dependencies for this target.
include pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/compiler_depend.make

# Include the progress variables for this target.
include pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/progress.make

pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild: pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete

pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-install
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-mkdir
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-download
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-update
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-patch
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-configure
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-build
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/CMakeFiles
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-done

pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-build: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing build step for 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pioasm && $(MAKE)

pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-configure: pimoroni-drivers/sdcard/pioasm/tmp/PioasmBuild-cfgcmd.txt
pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-configure: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Performing configure step for 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pioasm && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake "-GUnix Makefiles" /Users/speedhacker/pico/libs/pico-sdk/tools/pioasm
	cd /Users/speedhacker/pico/devs/first/build/pioasm && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-configure

pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-download: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E echo_append
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-download

pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-install: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pioasm && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E echo_append
	cd /Users/speedhacker/pico/devs/first/build/pioasm && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-install

pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/libs/pico-sdk/tools/pioasm
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/devs/first/build/pioasm
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/tmp
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E make_directory /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-mkdir

pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-patch: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E echo_append
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-patch

pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-update: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/speedhacker/pico/devs/first/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No update step for 'PioasmBuild'"
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E echo_append
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E touch /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-update

PioasmBuild: pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild
PioasmBuild: pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild-complete
PioasmBuild: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-build
PioasmBuild: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-configure
PioasmBuild: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-download
PioasmBuild: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-install
PioasmBuild: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-mkdir
PioasmBuild: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-patch
PioasmBuild: pimoroni-drivers/sdcard/pioasm/src/PioasmBuild-stamp/PioasmBuild-update
PioasmBuild: pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/build.make
.PHONY : PioasmBuild

# Rule to build all files generated by this target.
pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/build: PioasmBuild
.PHONY : pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/build

pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/clean:
	cd /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard && $(CMAKE_COMMAND) -P CMakeFiles/PioasmBuild.dir/cmake_clean.cmake
.PHONY : pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/clean

pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/depend:
	cd /Users/speedhacker/pico/devs/first/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/speedhacker/pico/devs/first /Users/speedhacker/pico/libs/pimoroni-pico/drivers/sdcard /Users/speedhacker/pico/devs/first/build /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard /Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pimoroni-drivers/sdcard/CMakeFiles/PioasmBuild.dir/depend

