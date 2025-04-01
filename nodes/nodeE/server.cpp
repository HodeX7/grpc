#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "data.grpc.pb.h"

class DataServiceImpl final : public data::DataService::Service {
public:
    grpc::Status PushData(grpc::ServerContext* context, const data::DataMessage* request, data::Empty* response) override {
        std::cout << "Node E: Received ID " << request->id() << "\n";
        // Store the received data (you can implement storage logic here)
        return grpc::Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50054");
    DataServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Node E: Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
