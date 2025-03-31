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
│   ├── hello_pb2.py
│   └── hello_pb2_grpc.py
├── protos/
│   └── hello.proto
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
     - Added proper namespace (`package hello;`) in proto file
     - Implemented HelloServiceImpl class with SayHello method
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
         ./protos/hello.proto
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
- Implements a simple "Hello" service:
  - Client sends a name ("Akshar")
  - Server responds with "Hello, Akshar"
  - Successful bidirectional communication established

### Key Files

1. **hello.proto**

```protobuf
syntax = "proto3";
package hello;

service HelloService {
  rpc SayHello (HelloRequest) returns (HelloReply);
}

message HelloRequest {
  string name = 1;
}

message HelloReply {
  string message = 1;
}
```

2. **server.cpp** (key parts)

```cpp
class HelloServiceImpl final : public HelloService::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
    std::cout << "Received request from: " << request->name() << std::endl;
    reply->set_message("Hello, " + request->name());
    return Status::OK;
  }
};
```

3. **client.py** (key parts)

```python
def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = hello_pb2_grpc.HelloServiceStub(channel)
    response = stub.SayHello(hello_pb2.HelloRequest(name='Akshar'))
    print("Received response: " + response.message)
```

### Next Steps

- Implement secure communication using SSL/TLS
- Add more complex service methods
- Implement error handling and timeouts
- Add unit tests and integration tests
