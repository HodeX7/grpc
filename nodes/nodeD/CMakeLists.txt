cmake_minimum_required(VERSION 3.10)
project(grpc_server)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# M1-specific configurations
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Set paths for Homebrew packages
set(PROTOBUF_ROOT "/opt/homebrew/opt/protobuf")
set(GRPC_ROOT "/opt/homebrew/opt/grpc")
set(GRPC_CPP_PLUGIN_EXECUTABLE "/opt/homebrew/bin/grpc_cpp_plugin")

# Find required packages with explicit paths
find_package(Protobuf REQUIRED PATHS ${PROTOBUF_ROOT})
find_package(gRPC REQUIRED PATHS ${GRPC_ROOT})
find_package(absl REQUIRED)
find_package(nlohmann_json REQUIRED)

# Set proto file paths
get_filename_component(PROTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../protos" ABSOLUTE)
get_filename_component(PROTO_FILE "${PROTO_PATH}/data.proto" ABSOLUTE)

# Generate protobuf files
set(PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}/data.pb.cc")
set(PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}/data.pb.h")
set(GRPC_SRCS "${CMAKE_CURRENT_BINARY_DIR}/data.grpc.pb.cc")
set(GRPC_HDRS "${CMAKE_CURRENT_BINARY_DIR}/data.grpc.pb.h")

# Custom command to generate protobuf and gRPC code
add_custom_command(
    OUTPUT "${PROTO_SRCS}" "${PROTO_HDRS}" "${GRPC_SRCS}" "${GRPC_HDRS}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}"
    COMMAND protoc
        -I${PROTO_PATH}
        --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
        --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
        ${PROTO_FILE}
    DEPENDS "${PROTO_FILE}"
    COMMENT "Generating gRPC and Protobuf files"
    VERBATIM
)

# Create a custom target for the generated files
add_custom_target(grpc_proto_gen DEPENDS "${PROTO_SRCS}" "${PROTO_HDRS}" "${GRPC_SRCS}" "${GRPC_HDRS}")

# Include directories
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS}
    ${gRPC_INCLUDE_DIRS}
    ${absl_INCLUDE_DIRS}
)

# Build the server
add_executable(server 
    server.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

add_dependencies(server grpc_proto_gen)

target_link_libraries(server 
    PRIVATE 
    protobuf::libprotobuf
    gRPC::grpc++
    gRPC::grpc++_reflection
    absl::strings
    absl::flat_hash_map
    absl::status
    absl::statusor
    nlohmann_json::nlohmann_json
) 