cmake_minimum_required(VERSION 3.10)
project(grpc_server)

set(CMAKE_CXX_STANDARD 17)

# M1-specific configurations
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0")

# Set policy for ROOT variables
cmake_policy(SET CMP0074 NEW)

# Set explicit paths for M1 Mac
set(Protobuf_ROOT "/opt/homebrew/opt/protobuf")
set(gRPC_ROOT "/opt/homebrew/opt/grpc")

# Find packages with specific paths
find_package(Protobuf REQUIRED PATHS "/opt/homebrew/opt/protobuf")
find_package(gRPC REQUIRED PATHS "/opt/homebrew/opt/grpc")

# Get absolute path to protoc and plugins
get_target_property(PROTOC_PATH protobuf::protoc LOCATION)

# Set proto file paths
get_filename_component(PROTO_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../protos" ABSOLUTE)
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
    COMMAND ${CMAKE_COMMAND} -E env
        ${PROTOC_PATH}
            -I${PROTO_PATH}
            --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
            --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
            --plugin=protoc-gen-grpc=/opt/homebrew/Cellar/grpc/1.71.0/bin/grpc_cpp_plugin
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
)
