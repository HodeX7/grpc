#include <grpcpp/grpcpp.h>
#include "data.grpc.pb.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <unistd.h>
#include <limits.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using data::DataMessage;
using data::Empty;
using data::DataService;

using json = nlohmann::json;

class DataServiceImpl final : public DataService::Service {
private:
    std::unordered_set<int> stored_ids;  // Declare stored_ids to track unique IDs

public:
    Status PushData(ServerContext* context, const DataMessage* request, Empty* reply) override {
        if (stored_ids.find(request->id()) != stored_ids.end()) {
            return Status(grpc::ALREADY_EXISTS, "Duplicate ID");
        }
        stored_ids.insert(request->id());

        int hash = request->id() % 3;

        if (hash != 2) { // Not D's responsibility
            // Forward to Node E
            auto channel = grpc::CreateChannel("localhost:50054", grpc::InsecureChannelCredentials());
            std::unique_ptr<DataService::Stub> client(DataService::NewStub(channel));
            grpc::ClientContext client_context;  // Create a ClientContext
            client->PushData(&client_context, *request, reply);  // Pass the ClientContext
        } else {
            // Store locally
            std::cout << "Node D: Stored ID " << request->id() << "\n";
        }
        return Status::OK;
    }
};

json load_config() {
    std::ifstream f("config.json");
    if (!f.is_open()) {
        std::cerr << "Error: Could not open config.json" << std::endl;
        throw std::runtime_error("Could not open config.json");
    }
    return json::parse(f);
}

int main() {
    try {
        // Load configuration
        json config = load_config();
        std::string server_address("0.0.0.0:50053");
        
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            std::cout << "Current working dir: " << cwd << std::endl;
        } else {
            perror("getcwd() error");
        }
        
        std::cout << "Node D: Starting server on " << server_address << std::endl;

        DataServiceImpl service;
        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<Server> server(builder.BuildAndStart());
        
        std::cout << "Node D: Server started successfully" << std::endl;
        server->Wait();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}