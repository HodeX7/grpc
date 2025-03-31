// #include <grpcpp/grpcpp.h>
// #include "../build/hello.grpc.pb.h"
// #include <iostream>

// using grpc::Server;
// using grpc::ServerBuilder;
// using grpc::ServerContext;
// using grpc::Status;
// using hello::HelloRequest;
// using hello::HelloReply;
// using hello::HelloService;

// class HelloServiceImpl final : public HelloService::Service {
//   Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
//     std::cout << "Received request from: " << request->name() << std::endl;
//     reply->set_message("Hello, " + request->name());
//     return Status::OK;
//   }
// };

// int main() {
//   try {
//     std::string server_address("0.0.0.0:50051");
//     HelloServiceImpl service;

//     ServerBuilder builder;
//     builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//     builder.RegisterService(&service);
    
//     std::cout << "Starting server on " << server_address << std::endl;
//     std::unique_ptr<Server> server(builder.BuildAndStart());
    
//     if (!server) {
//       std::cerr << "Failed to start server" << std::endl;
//       return 1;
//     }
    
//     std::cout << "Server started successfully" << std::endl;
//     server->Wait();
    
//   } catch (const std::exception& e) {
//     std::cerr << "Exception caught: " << e.what() << std::endl;
//     return 1;
//   }
  
//   return 0;
// }



#include <grpcpp/grpcpp.h>
#include "data.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using data::DataMessage;
using data::Empty;
using data::DataService;

class DataServiceImpl final : public DataService::Service {
  Status PushData(ServerContext* context, const DataMessage* request, Empty* reply) override {
    // Log the received data
    std::cout << "Received data [ID: " << request->id() 
              << ", Size: " << request->payload().size() 
              << " bytes, Time: " << request->timestamp() << "]\n";
    return Status::OK;
  }
};

int main() {
  std::string server_address("0.0.0.0:50051");
  DataServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  server->Wait();
  return 0;
}