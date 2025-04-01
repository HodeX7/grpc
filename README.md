# gRPC Project Documentation

## Step 1: Setting up gRPC Server (C++) and Client (Python)

### Project Structure

```
grpc-project/
├── cpp/
│   ├── CMakeLists.txt
│   └── server.cpp
├── python/
│   ├── client.py
│   ├── data_pb2.py
│   └── data_pb2_grpc.py
├── protos/
│   └── data.proto
├── build/
└── venv/
```

### Initial Setup and Issues Faced

1. **CMake Configuration Issues**

   - **Problem**: Build failures due to incorrect paths and M1 architecture compatibility
   - **Solution**: Updated CMakeLists.txt with:
     - Set minimum CMake version to 3.10
     - Configured C++17 standard
     - Added proper paths for Protobuf and gRPC
     - Fixed spaces in directory paths

2. **Protobuf Generation Issues**

   - **Problem**: `protoc` command failing due to spaces in paths
   - **Solution**: Updated CMake configuration to properly handle spaces in paths and generate protobuf files

3. **Server Implementation**

   - **Problem**: Server not properly handling gRPC service implementation
   - **Solution**:
     - Added proper namespace (`package data;`) in proto file
     - Implemented DataServiceImpl class with PushData method
     - Added error handling and logging in server code

4. **Python Client Issues**

   - **Problem**: Python environment and dependency issues
   - **Solution**:

     ```bash
     # Create Python virtual environment
     python3 -m venv venv
     source venv/bin/activate

     # Install required packages
     pip install grpcio grpcio-tools

     # Generate Python protobuf files
     python -m grpc_tools.protoc -I./protos \
         --python_out=./python \
         --grpc_python_out=./python \
         ./protos/data.proto
     ```

### How to Run

1. **Build and Start the Server**

```bash
# Create build directory and build the project
mkdir -p build && cd build
cmake ../cpp
make

# Run the server
./server
```

2. **Run the Python Client**

```bash
# Activate virtual environment
source venv/bin/activate

# Run the client
cd python
python client.py
```

### Current Functionality

- Server listens on `0.0.0.0:50051`
- Client connects to server using insecure channel
- Implements a data push service:
  - Client sends data messages with ID, payload, and timestamp
  - Server logs received data and acknowledges receipt
  - One-way communication (client to server)

### Key Files

1. **data.proto**

```protobuf
syntax = "proto3";
package data;

service DataService {
  rpc PushData (DataMessage) returns (Empty); // One-way communication (no reply)
}

message DataMessage {
  int32 id = 1;          // Unique ID for the data
  bytes payload = 2;      // Raw data (e.g., file contents)
  string timestamp = 3;   // Time of data creation
}

message Empty {}          // Empty response
```

2. **server.cpp** (key parts)

```cpp
class DataServiceImpl final : public DataService::Service {
  Status PushData(ServerContext* context, const DataMessage* request, Empty* reply) override {
    std::cout << "Received data [ID: " << request->id()
              << ", Size: " << request->payload().size()
              << " bytes, Time: " << request->timestamp() << "]\n";
    return Status::OK;
  }
};
```

3. **client.py** (key parts)

```python
def generate_data(id):
    return data_pb2.DataMessage(
        id=id,
        payload=b"Sample payload",  # Simulate binary data
        timestamp=str(time.time())
    )

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = data_pb2_grpc.DataServiceStub(channel)

    # Send 3 data points
    for i in range(1, 4):
        data = generate_data(i)
        stub.PushData(data)
        print(f"Sent data ID: {i}")
```

### Next Steps

- Implement secure communication using SSL/TLS
- Add data validation and error handling
- Implement data persistence on server side
- Add unit tests and integration tests
- Add support for different types of data payloads

## Step 2: Upgrading to Data Service Implementation

### Changes Made

1. **Proto File Update**

   - Changed from `hello.proto` to `data.proto`
   - Updated service definition to handle data messages
   - Added new message types for data transfer

2. **Server Implementation Changes**

   - Updated server code to implement `DataService` instead of `HelloService`
   - Added logging for received data messages
   - Implemented one-way communication pattern

3. **Client Implementation Changes**

   - Updated client to send data messages instead of hello messages
   - Added data generation function with ID, payload, and timestamp
   - Implemented batch sending of multiple data points

4. **Build System Updates**
   - Updated CMakeLists.txt to use new proto file
   - Modified protobuf generation paths
   - Updated include paths and dependencies

### New Functionality

- One-way data transfer service
- Support for binary payloads
- Timestamp tracking for data messages
- Batch processing capability
- Detailed server-side logging

### Technical Details

1. **Data Message Structure**

```protobuf
message DataMessage {
  int32 id = 1;          // Unique identifier for each message
  bytes payload = 2;      // Binary data payload
  string timestamp = 3;   // Creation timestamp
}
```

2. **Server Logging**

```cpp
std::cout << "Received data [ID: " << request->id()
          << ", Size: " << request->payload().size()
          << " bytes, Time: " << request->timestamp() << "]\n";
```

3. **Client Data Generation**

```python
def generate_data(id):
    return data_pb2.DataMessage(
        id=id,
        payload=b"Sample payload",  # Binary data
        timestamp=str(time.time())
    )
```

### Migration Process

1. Created new proto file with data service definition
2. Updated server implementation to handle data messages
3. Modified client to generate and send data messages
4. Updated build system configuration
5. Regenerated protobuf files for both C++ and Python
6. Updated documentation to reflect changes

### Next Steps for Step 2

- Implement data validation on server side
- Add support for different payload types
- Implement data persistence
- Add error handling for malformed data
- Implement data compression for large payloads

## Step 3: Multi-Node Architecture Implementation

### Changes Made

1. **Extended the system by adding Node C and Node D**
2. **Implemented round-robin forwarding mechanism in Node B**
3. **Added configuration files for all nodes:**
   - Node A: Configures target server (Node B)
   - Node B: Configures forwarding to Nodes C and D
   - Node C and D: Basic node configurations as leaf nodes

### Issues and Solutions:

1. **Build Issues**:

   - Fixed protobuf generation command in CMakeLists.txt
   - Resolved linking issues with Abseil libraries
   - Added proper M1-specific configurations for macOS

2. **Configuration Issues**:

   - Fixed empty config files for Node C and D
   - Implemented proper JSON structure for all node configurations
   - Added error handling for config file loading

3. **Terminal Management**:
   - Improved terminal window management for better visibility
   - Fixed path handling with spaces in directory names
   - Added proper delays between node startups

### Current Architecture:

- Node A (Python client): Sends data to Node B
- Node B (C++ server): Receives data and forwards alternately to C and D
- Node C (C++ server): Receives data with odd IDs
- Node D (C++ server): Receives data with even IDs

### Port Configuration:

- Node A: Client only (no port)
- Node B: Server on port 50051
- Node C: Server on port 50052
- Node D: Server on port 50053

### Next Steps:

1. Implement error handling and recovery mechanisms
2. Add monitoring and metrics collection
3. Implement data persistence
4. Add load balancing capabilities

## Step 4: Shared Memory Implementation in Node B

### Overview

Node B implements shared memory using Boost.Interprocess library to maintain state and coordinate message forwarding between Nodes C and D. This implementation is specific to Node B because:

1. Nodes C and D are intended to run on different physical machines
2. Shared memory is most effective for inter-process communication on the same machine
3. Node B acts as the central coordinator in the overlay network

### Implementation Details

- Location: `/dev/shm/aksharmehta_counter` (user-specific shared memory segment)
- Components:
  - Shared Data Structure:
    ```cpp
    struct SharedData {
        int counter;                    // Total messages processed
        int last_target;               // Last node forwarded to (C or D)
        std::vector<int> message_history;  // Last 10 messages processed
    };
    ```
  - Named Mutex: Ensures thread-safe access to shared data
  - Memory Mapping: Maps shared memory segment for process access

### Purpose and Benefits

1. **State Persistence**

   - Maintains message count across multiple requests
   - Tracks forwarding history for load balancing
   - Enables round-robin distribution between Nodes C and D

2. **Load Balancing**

   - Ensures even distribution of messages between Nodes C and D
   - Prevents overloading of a single downstream node
   - Maintains fairness in the overlay network

3. **Performance Optimization**
   - Reduces memory allocation overhead
   - Minimizes synchronization overhead
   - Provides fast access to shared state

### Effects on Overlay Network

1. **Reliability**

   - Node B maintains consistent state even if individual requests fail
   - Prevents message loss during network issues
   - Enables recovery from temporary failures

2. **Scalability**

   - Efficient handling of high message volumes
   - Reduced memory usage through shared resources
   - Better resource utilization

3. **Monitoring and Debugging**
   - Real-time visibility into message flow
   - Easy tracking of system state
   - Simplified troubleshooting

### Technical Considerations

1. **Security**

   - User-specific shared memory segments
   - Proper permission handling
   - Isolation between different users

2. **Resource Management**

   - Automatic cleanup of shared memory
   - Proper mutex locking/unlocking
   - Memory leak prevention

3. **Error Handling**
   - Graceful degradation if shared memory fails
   - Fallback to regular memory if needed
   - Comprehensive error logging

### Future Improvements

1. **Monitoring**

   - Add metrics collection
   - Implement health checks
   - Enhanced logging capabilities

2. **Performance**

   - Optimize memory usage
   - Fine-tune synchronization
   - Implement caching strategies

3. **Reliability**
   - Add backup mechanisms
   - Implement recovery procedures
   - Enhanced error handling

## Milestone: Shared Memory Integration with Routing Logic

### Overview

In this milestone, we implemented and integrated shared memory functionality with the routing logic in Node B. This enhancement provides persistent state management, improved message tracking, and better monitoring capabilities for the overlay network.

### Implementation Details

1. **Shared Memory Structure**

   ```cpp
   struct SharedData {
       int counter;           // Total messages processed
       int last_target;      // Last target node (C or D)
       std::vector<int> recent_ids;  // Message history
   };
   ```

2. **Key Components**

   - Shared memory segment at `/dev/shm/aksharmehta_counter`
   - Named mutex for thread-safe access
   - Persistent state across message processing
   - Monitoring endpoint for state inspection

3. **Routing Logic Integration**
   - Messages routed based on ID (odd/even)
   - State tracking in shared memory
   - Thread-safe operations with mutex locks

### Purpose and Benefits

1. **State Persistence**

   - Maintains message processing history
   - Tracks routing decisions
   - Enables system recovery after restarts

2. **Load Balancing**

   - Consistent routing decisions
   - Even distribution between nodes C and D
   - Prevents message loss during processing

3. **Monitoring and Debugging**
   - Real-time state inspection
   - Message history tracking
   - Performance metrics collection

### Achievements

1. **Successfully Implemented**

   - Shared memory initialization and management
   - Thread-safe state updates
   - Message history tracking
   - Monitoring endpoint

2. **Verified Functionality**

   - Correct message routing (odd/even distribution)
   - State persistence across messages
   - Proper mutex synchronization
   - Monitoring capabilities

3. **Current Status**
   - Node B successfully processes messages
   - Maintains state in shared memory
   - Forwards messages to appropriate nodes
   - Provides monitoring capabilities

### Next Steps

1. **Testing and Validation**

   - Implement comprehensive test suite
   - Verify concurrent message handling
   - Test system recovery scenarios
   - Validate monitoring endpoint

2. **Performance Optimization**

   - Optimize shared memory access patterns
   - Improve mutex contention handling
   - Enhance message history management
   - Fine-tune monitoring overhead

3. **Integration with Other Nodes**

   - Implement similar functionality in Nodes C and D
   - Add message deduplication
   - Enhance error handling
   - Improve logging and monitoring

4. **Documentation and Maintenance**
   - Document shared memory usage patterns
   - Create maintenance procedures
   - Update system architecture diagrams
   - Prepare deployment guidelines

### Technical Considerations

1. **Security**

   - Shared memory permissions
   - Access control mechanisms
   - Data integrity protection
   - Error handling

2. **Resource Management**

   - Memory allocation
   - Cleanup procedures
   - Resource limits
   - Performance monitoring

3. **Error Handling**
   - Shared memory failures
   - Mutex deadlocks
   - Message processing errors
   - Recovery procedures

### Next Steps

1. **Integrate Shared Memory with Routing Logic**

   - Ensure that the shared memory implementation is fully integrated with the routing logic in Node B.
   - Verify that messages are being routed correctly to Nodes C and D based on the shared state.

2. **Implement Monitoring Endpoint**

   - Finalize the `GetSharedState` endpoint to allow external monitoring of the shared memory state.
   - Ensure that the endpoint provides accurate and real-time data about message processing and routing.

3. **Testing and Validation**

   - Develop a comprehensive test suite to validate the functionality of the shared memory and routing logic.
   - Conduct tests for concurrent message handling to ensure thread safety and data integrity.
   - Validate the monitoring endpoint to ensure it returns the correct shared state.

4. **Documentation**

   - Update the project documentation to include details about the shared memory implementation and routing logic.
   - Document the usage of the monitoring endpoint and how to access shared memory state.

5. **Integration with Other Nodes**

   - Implement similar shared memory functionality in Nodes C and D to maintain consistency across the system.
   - Ensure that all nodes can communicate effectively and share state as needed.

6. **Performance Optimization**

   - Analyze the performance of the shared memory implementation and identify any bottlenecks.
   - Optimize memory access patterns and mutex usage to improve overall system performance.

7. **Deployment Preparation**

   - Prepare the system for deployment, ensuring that all nodes are configured correctly.
   - Create deployment guidelines and instructions for setting up the entire system in a production environment.

8. **Monitoring and Maintenance**
   - Set up monitoring tools to track the performance and health of the system in real-time.
   - Establish maintenance procedures to handle potential issues and ensure system reliability.
