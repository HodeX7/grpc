# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build"

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

data.pb.cc: /Users/aksharmehta/SJSU\ COURSES/CMPE\ 275/grpc-project/protos/data.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating gRPC and Protobuf files"
	/opt/homebrew/bin/cmake -E make_directory "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build"
	protoc "-I/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/protos" "--cpp_out=/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build" "--grpc_out=/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build" --plugin=protoc-gen-grpc=/opt/homebrew/bin/grpc_cpp_plugin "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/protos/data.proto"

data.pb.h: data.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate data.pb.h

data.grpc.pb.cc: data.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate data.grpc.pb.cc

data.grpc.pb.h: data.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate data.grpc.pb.h

CMakeFiles/server.dir/codegen:
.PHONY : CMakeFiles/server.dir/codegen

CMakeFiles/server.dir/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.cpp.o: /Users/aksharmehta/SJSU\ COURSES/CMPE\ 275/grpc-project/nodes/nodeB/server.cpp
CMakeFiles/server.dir/server.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/server.cpp.o -MF CMakeFiles/server.dir/server.cpp.o.d -o CMakeFiles/server.dir/server.cpp.o -c "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/server.cpp"

CMakeFiles/server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/server.cpp" > CMakeFiles/server.dir/server.cpp.i

CMakeFiles/server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/server.cpp" -o CMakeFiles/server.dir/server.cpp.s

CMakeFiles/server.dir/data.pb.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/data.pb.cc.o: data.pb.cc
CMakeFiles/server.dir/data.pb.cc.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/data.pb.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/data.pb.cc.o -MF CMakeFiles/server.dir/data.pb.cc.o.d -o CMakeFiles/server.dir/data.pb.cc.o -c "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/data.pb.cc"

CMakeFiles/server.dir/data.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/data.pb.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/data.pb.cc" > CMakeFiles/server.dir/data.pb.cc.i

CMakeFiles/server.dir/data.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/data.pb.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/data.pb.cc" -o CMakeFiles/server.dir/data.pb.cc.s

CMakeFiles/server.dir/data.grpc.pb.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/data.grpc.pb.cc.o: data.grpc.pb.cc
CMakeFiles/server.dir/data.grpc.pb.cc.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/data.grpc.pb.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/data.grpc.pb.cc.o -MF CMakeFiles/server.dir/data.grpc.pb.cc.o.d -o CMakeFiles/server.dir/data.grpc.pb.cc.o -c "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/data.grpc.pb.cc"

CMakeFiles/server.dir/data.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/data.grpc.pb.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/data.grpc.pb.cc" > CMakeFiles/server.dir/data.grpc.pb.cc.i

CMakeFiles/server.dir/data.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/data.grpc.pb.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/data.grpc.pb.cc" -o CMakeFiles/server.dir/data.grpc.pb.cc.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.cpp.o" \
"CMakeFiles/server.dir/data.pb.cc.o" \
"CMakeFiles/server.dir/data.grpc.pb.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server.cpp.o
server: CMakeFiles/server.dir/data.pb.cc.o
server: CMakeFiles/server.dir/data.grpc.pb.cc.o
server: CMakeFiles/server.dir/build.make
server: /Users/aksharmehta/miniconda3/lib/libgrpc++_reflection.1.71.0.dylib
server: /opt/homebrew/lib/libboost_system.dylib
server: /Users/aksharmehta/miniconda3/lib/libgrpc++.1.71.0.dylib
server: /Users/aksharmehta/miniconda3/lib/libprotobuf.29.3.0.dylib
server: /opt/homebrew/lib/libabsl_leak_check.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_die_if_null.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_initialize.2407.0.0.dylib
server: /Users/aksharmehta/miniconda3/lib/libgrpc.46.0.0.dylib
server: /opt/homebrew/lib/libabsl_statusor.2407.0.0.dylib
server: /opt/homebrew/Cellar/openssl@1.1/1.1.1w/lib/libssl.dylib
server: /opt/homebrew/Cellar/openssl@1.1/1.1.1w/lib/libcrypto.dylib
server: /Users/aksharmehta/miniconda3/lib/libgpr.46.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_distributions.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_seed_sequences.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_internal_pool_urbg.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_internal_randen.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_internal_randen_hwaes.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_internal_randen_hwaes_impl.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_internal_randen_slow.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_internal_platform.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_internal_seed_material.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_random_seed_gen_exception.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_status.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_check_op.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_conditions.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_message.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_strerror.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_nullguard.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_examine_stack.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_format.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_proto.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_log_sink_set.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_globals.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_globals.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_sink.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_entry.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_vlog_config_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_internal_fnmatch.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_marshalling.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_reflection.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_config.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_program_name.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_private_handle_accessor.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_commandlineflag.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_flags_commandlineflag_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_cord.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_cordz_info.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_cord_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_cordz_functions.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_cordz_handle.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_crc_cord_state.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_crc32c.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_crc_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_crc_cpu_detect.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_raw_hash_set.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_hashtablez_sampler.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_exponential_biased.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_hash.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_bad_variant_access.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_city.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_low_level_hash.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_bad_optional_access.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_synchronization.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_stacktrace.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_symbolize.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_debugging_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_demangle_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_demangle_rust.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_decode_rust_punycode.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_utf8_for_code_point.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_graphcycles_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_kernel_timeout_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_time.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_civil_time.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_time_zone.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_malloc_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_str_format_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_strings.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_strings_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_string_view.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_base.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_spinlock_wait.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_throw_delegate.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_raw_logging_internal.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_log_severity.2407.0.0.dylib
server: /opt/homebrew/lib/libabsl_int128.2407.0.0.dylib
server: /Users/aksharmehta/miniconda3/lib/libupb.a
server: /opt/homebrew/lib/libutf8_range.dylib
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend: data.grpc.pb.cc
CMakeFiles/server.dir/depend: data.grpc.pb.h
CMakeFiles/server.dir/depend: data.pb.cc
CMakeFiles/server.dir/depend: data.pb.h
	cd "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB" "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB" "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build" "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build" "/Users/aksharmehta/SJSU COURSES/CMPE 275/grpc-project/nodes/nodeB/build/CMakeFiles/server.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/server.dir/depend

