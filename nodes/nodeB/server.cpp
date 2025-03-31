#include <grpcpp/grpcpp.h>
#include "data.grpc.pb.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <memory>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::Channel;
using grpc::ClientContext;
using grpc::CreateChannel;
using data::DataMessage;
using data::Empty;
using data::DataService;
using json = nlohmann::json;

// Client class for forwarding data
class DataServiceClient {
 public:
  DataServiceClient(std::shared_ptr<Channel> channel)
      : stub_(DataService::NewStub(channel)) {}

  void PushData(const DataMessage& request) {
    Empty reply;
    ClientContext context;
    Status status = stub_->PushData(&context, request, &reply);
    if (!status.ok()) {
      std::cerr << "Error forwarding data: " << status.error_message() << std::endl;
    }
  }

 private:
  std::unique_ptr<DataService::Stub> stub_;
};

class DataServiceImpl final : public DataService::Service {
 public:
  DataServiceImpl(const json& config) : config_(config) {}

  Status PushData(ServerContext* context, const DataMessage* request, Empty* reply) override {
    std::cout << "NodeB: Received data ID " << request->id() << "\n";

    // Forward to Node C or D (round-robin)
    static bool toggle = false;
    const auto& edges = config_["edges"];
    const auto& target_edge = edges[toggle ? 1 : 0]; // First edge is C, second is D
    std::string target = target_edge["ip"].get<std::string>() + ":" + std::to_string(target_edge["port"].get<int>());
    std::string target_name = target_edge["id"].get<std::string>();
    toggle = !toggle;

    std::cout << "NodeB: Forwarding data ID " << request->id() << " to " << target_name << " at " << target << std::endl;

    auto channel = CreateChannel(target, grpc::InsecureChannelCredentials());
    DataServiceClient client(channel);
    client.PushData(*request);

    return Status::OK;
  }

 private:
  json config_;
};

json load_config() {
    std::ifstream f("config.json");
    return json::parse(f);
}

int main() {
    try {
        // Load configuration
        json config = load_config();
        std::string server_address("0.0.0.0:50051");
        
        std::cout << "NodeB: Starting server on " << server_address << std::endl;
        std::cout << "NodeB: Configured edges:" << std::endl;
        for (const auto& edge : config["edges"]) {
            std::cout << "  - " << edge["id"] << " at " 
                      << edge["ip"] << ":" << edge["port"] << std::endl;
        }

        DataServiceImpl service(config);
        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<Server> server(builder.BuildAndStart());
        
        std::cout << "NodeB: Server started successfully" << std::endl;
        server->Wait();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}