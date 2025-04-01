#!/bin/bash

# Store the original directory
ORIGINAL_DIR=$(pwd)

# Build Node B (C++ server)
echo "Building Node B (C++ server)..."
cd nodes/nodeB
mkdir -p build
cd build
cmake .. && make || { echo "Node B build failed"; exit 1; }

# Build Node C (C++ server)
echo "Building Node C (C++ server)..."
cd ../../nodeC
mkdir -p build
cd build
cmake .. && make || { echo "Node C build failed"; exit 1; }

# Build Node D (C++ server)
echo "Building Node D (C++ server)..."
cd ../../nodeD
mkdir -p build
cd build
cmake .. && make || { echo "Node D build failed"; exit 1; }

# Generate Python protobuf files for Node A
echo "Generating Python protobuf files for Node A..."
cd "$ORIGINAL_DIR"
python -m grpc_tools.protoc \
    -I./protos \
    --python_out=./nodes/nodeA \
    --grpc_python_out=./nodes/nodeA \
    ./protos/data.proto

echo "Build complete!" 