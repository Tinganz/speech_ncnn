# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tingan/Desktop/未命名文件夹/speech_ncnn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build

# Include any dependencies generated for this target.
include imgui/CMakeFiles/imgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include imgui/CMakeFiles/imgui.dir/compiler_depend.make

# Include the progress variables for this target.
include imgui/CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include imgui/CMakeFiles/imgui.dir/flags.make

imgui/CMakeFiles/imgui.dir/imgui.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/imgui.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui.cpp
imgui/CMakeFiles/imgui.dir/imgui.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object imgui/CMakeFiles/imgui.dir/imgui.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/imgui.cpp.o -MF CMakeFiles/imgui.dir/imgui.cpp.o.d -o CMakeFiles/imgui.dir/imgui.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui.cpp

imgui/CMakeFiles/imgui.dir/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui.cpp > CMakeFiles/imgui.dir/imgui.cpp.i

imgui/CMakeFiles/imgui.dir/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui.cpp -o CMakeFiles/imgui.dir/imgui.cpp.s

imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_draw.cpp
imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o -MF CMakeFiles/imgui.dir/imgui_draw.cpp.o.d -o CMakeFiles/imgui.dir/imgui_draw.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_draw.cpp

imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_draw.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_draw.cpp > CMakeFiles/imgui.dir/imgui_draw.cpp.i

imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_draw.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_draw.cpp -o CMakeFiles/imgui.dir/imgui_draw.cpp.s

imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_widgets.cpp
imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o -MF CMakeFiles/imgui.dir/imgui_widgets.cpp.o.d -o CMakeFiles/imgui.dir/imgui_widgets.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_widgets.cpp

imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_widgets.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_widgets.cpp > CMakeFiles/imgui.dir/imgui_widgets.cpp.i

imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_widgets.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_widgets.cpp -o CMakeFiles/imgui.dir/imgui_widgets.cpp.s

imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_tables.cpp
imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.o -MF CMakeFiles/imgui.dir/imgui_tables.cpp.o.d -o CMakeFiles/imgui.dir/imgui_tables.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_tables.cpp

imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_tables.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_tables.cpp > CMakeFiles/imgui.dir/imgui_tables.cpp.i

imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_tables.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_tables.cpp -o CMakeFiles/imgui.dir/imgui_tables.cpp.s

imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_helper.cpp
imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.o -MF CMakeFiles/imgui.dir/imgui_helper.cpp.o.d -o CMakeFiles/imgui.dir/imgui_helper.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_helper.cpp

imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_helper.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_helper.cpp > CMakeFiles/imgui.dir/imgui_helper.cpp.i

imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_helper.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_helper.cpp -o CMakeFiles/imgui.dir/imgui_helper.cpp.s

imgui/CMakeFiles/imgui.dir/imgui_user.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/imgui_user.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_user.cpp
imgui/CMakeFiles/imgui.dir/imgui_user.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object imgui/CMakeFiles/imgui.dir/imgui_user.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/imgui_user.cpp.o -MF CMakeFiles/imgui.dir/imgui_user.cpp.o.d -o CMakeFiles/imgui.dir/imgui_user.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_user.cpp

imgui/CMakeFiles/imgui.dir/imgui_user.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_user.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_user.cpp > CMakeFiles/imgui.dir/imgui_user.cpp.i

imgui/CMakeFiles/imgui.dir/imgui_user.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_user.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_user.cpp -o CMakeFiles/imgui.dir/imgui_user.cpp.s

imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_stdlib.cpp
imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.o -MF CMakeFiles/imgui.dir/imgui_stdlib.cpp.o.d -o CMakeFiles/imgui.dir/imgui_stdlib.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_stdlib.cpp

imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui_stdlib.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_stdlib.cpp > CMakeFiles/imgui.dir/imgui_stdlib.cpp.i

imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui_stdlib.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/imgui_stdlib.cpp -o CMakeFiles/imgui.dir/imgui_stdlib.cpp.s

imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/dir_iterate.cpp
imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.o -MF CMakeFiles/imgui.dir/dir_iterate.cpp.o.d -o CMakeFiles/imgui.dir/dir_iterate.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/dir_iterate.cpp

imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/dir_iterate.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/dir_iterate.cpp > CMakeFiles/imgui.dir/dir_iterate.cpp.i

imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/dir_iterate.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/dir_iterate.cpp -o CMakeFiles/imgui.dir/dir_iterate.cpp.s

imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_narrow.cpp
imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o -MF CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o.d -o CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_narrow.cpp

imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_narrow.cpp > CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.i

imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_narrow.cpp -o CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.s

imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_weihei.cpp
imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o -MF CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o.d -o CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_weihei.cpp

imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_weihei.cpp > CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.i

imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/fonts/mono_weihei.cpp -o CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.s

imgui/CMakeFiles/imgui.dir/icons/icons.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/icons/icons.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/icons.cpp
imgui/CMakeFiles/imgui.dir/icons/icons.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object imgui/CMakeFiles/imgui.dir/icons/icons.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/icons/icons.cpp.o -MF CMakeFiles/imgui.dir/icons/icons.cpp.o.d -o CMakeFiles/imgui.dir/icons/icons.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/icons.cpp

imgui/CMakeFiles/imgui.dir/icons/icons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/icons/icons.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/icons.cpp > CMakeFiles/imgui.dir/icons/icons.cpp.i

imgui/CMakeFiles/imgui.dir/icons/icons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/icons/icons.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/icons.cpp -o CMakeFiles/imgui.dir/icons/icons.cpp.s

imgui/CMakeFiles/imgui.dir/icons/folder.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/icons/folder.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/folder.cpp
imgui/CMakeFiles/imgui.dir/icons/folder.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object imgui/CMakeFiles/imgui.dir/icons/folder.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/icons/folder.cpp.o -MF CMakeFiles/imgui.dir/icons/folder.cpp.o.d -o CMakeFiles/imgui.dir/icons/folder.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/folder.cpp

imgui/CMakeFiles/imgui.dir/icons/folder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/icons/folder.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/folder.cpp > CMakeFiles/imgui.dir/icons/folder.cpp.i

imgui/CMakeFiles/imgui.dir/icons/folder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/icons/folder.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/folder.cpp -o CMakeFiles/imgui.dir/icons/folder.cpp.s

imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_solid.cpp
imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.o -MF CMakeFiles/imgui.dir/icons/fa_solid.cpp.o.d -o CMakeFiles/imgui.dir/icons/fa_solid.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_solid.cpp

imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/icons/fa_solid.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_solid.cpp > CMakeFiles/imgui.dir/icons/fa_solid.cpp.i

imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/icons/fa_solid.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_solid.cpp -o CMakeFiles/imgui.dir/icons/fa_solid.cpp.s

imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_regular.cpp
imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.o -MF CMakeFiles/imgui.dir/icons/fa_regular.cpp.o.d -o CMakeFiles/imgui.dir/icons/fa_regular.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_regular.cpp

imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/icons/fa_regular.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_regular.cpp > CMakeFiles/imgui.dir/icons/fa_regular.cpp.i

imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/icons/fa_regular.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/icons/fa_regular.cpp -o CMakeFiles/imgui.dir/icons/fa_regular.cpp.s

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_opengl3.cpp
imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o -MF CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_opengl3.cpp

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_opengl3.cpp > CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.i

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_opengl3.cpp -o CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.s

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_sdl.cpp
imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o -MF CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o.d -o CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_sdl.cpp

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_sdl.cpp > CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.i

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_sdl.cpp -o CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.s

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_glfw.cpp
imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o -MF CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o.d -o CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_glfw.cpp

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_glfw.cpp > CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.i

imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/backends/imgui_impl_glfw.cpp -o CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.s

imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o: imgui/CMakeFiles/imgui.dir/flags.make
imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/ImGuiFileDialog.cpp
imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o: imgui/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o -MF CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o.d -o CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o -c /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/ImGuiFileDialog.cpp

imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.i"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/ImGuiFileDialog.cpp > CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.i

imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.s"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui/ImGuiFileDialog.cpp -o CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/imgui.cpp.o" \
"CMakeFiles/imgui.dir/imgui_draw.cpp.o" \
"CMakeFiles/imgui.dir/imgui_widgets.cpp.o" \
"CMakeFiles/imgui.dir/imgui_tables.cpp.o" \
"CMakeFiles/imgui.dir/imgui_helper.cpp.o" \
"CMakeFiles/imgui.dir/imgui_user.cpp.o" \
"CMakeFiles/imgui.dir/imgui_stdlib.cpp.o" \
"CMakeFiles/imgui.dir/dir_iterate.cpp.o" \
"CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o" \
"CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o" \
"CMakeFiles/imgui.dir/icons/icons.cpp.o" \
"CMakeFiles/imgui.dir/icons/folder.cpp.o" \
"CMakeFiles/imgui.dir/icons/fa_solid.cpp.o" \
"CMakeFiles/imgui.dir/icons/fa_regular.cpp.o" \
"CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o" \
"CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o" \
"CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/imgui.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/imgui_draw.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/imgui_widgets.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/imgui_tables.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/imgui_helper.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/imgui_user.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/imgui_stdlib.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/dir_iterate.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/fonts/mono_narrow.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/fonts/mono_weihei.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/icons/icons.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/icons/folder.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/icons/fa_solid.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/icons/fa_regular.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/backends/imgui_impl_opengl3.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/backends/imgui_impl_sdl.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/backends/imgui_impl_glfw.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/ImGuiFileDialog.cpp.o
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/build.make
libimgui.1.89.20.06.dylib: imgui/CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX shared library ../libimgui.dylib"
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && $(CMAKE_COMMAND) -E cmake_symlink_library ../libimgui.1.89.20.06.dylib ../libimgui.1.dylib ../libimgui.dylib

libimgui.1.dylib: libimgui.1.89.20.06.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libimgui.1.dylib

libimgui.dylib: libimgui.1.89.20.06.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libimgui.dylib

# Rule to build all files generated by this target.
imgui/CMakeFiles/imgui.dir/build: libimgui.dylib
.PHONY : imgui/CMakeFiles/imgui.dir/build

imgui/CMakeFiles/imgui.dir/clean:
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : imgui/CMakeFiles/imgui.dir/clean

imgui/CMakeFiles/imgui.dir/depend:
	cd /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tingan/Desktop/未命名文件夹/speech_ncnn /Users/tingan/Desktop/未命名文件夹/speech_ncnn/imgui /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui /Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/imgui/CMakeFiles/imgui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : imgui/CMakeFiles/imgui.dir/depend

