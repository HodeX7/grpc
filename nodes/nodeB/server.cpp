#include <grpcpp/grpcpp.h>
#include "data.grpc.pb.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <sys/stat.h>
#include <errno.h>
#include <pwd.h>
#include <unistd.h>

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
using namespace boost::interprocess;

// Shared memory structure
struct SharedData {
    int counter;
    int last_target;  // 0 for C, 1 for D
    std::vector<int> message_history;  // Track last 10 messages
};

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
  DataServiceImpl(const json& config) : config_(config) {
    // Initialize shared memory
    if (!initializeSharedMemory()) {
      throw std::runtime_error("Failed to initialize shared memory");
    }
  }

  ~DataServiceImpl() {
    try {
      // Clean up shared memory
      try {
        shared_memory_object::remove("/tmp/grpc_shared_memory/counter");
        named_mutex::remove("/tmp/grpc_shared_memory/mutex");
      } catch (const std::exception& e) {
        // Ignore cleanup errors
      }
    } catch (const std::exception& e) {
      std::cerr << "Error cleaning up shared memory: " << e.what() << std::endl;
    }
  }

  Status PushData(ServerContext* context, const DataMessage* request, Empty* reply) override {
    std::cout << "NodeB: Received data ID " << request->id() << "\n";

    // Get shared data with mutex lock
    SharedData* data = static_cast<SharedData*>(region_->get_address());
    if (!data) {
      return Status(grpc::INTERNAL, "Failed to access shared memory");
    }

    // Lock mutex for thread safety
    scoped_lock<named_mutex> lock(*mutex_);

    // Update shared data
    data->counter++;
    data->last_target = request->id() % 2;  // 0 for C, 1 for D
    
    // Update message history
    if (data->message_history.size() >= 10) {
      data->message_history.erase(data->message_history.begin());
    }
    data->message_history.push_back(request->id());

    // Print shared memory state
    std::cout << "NodeB: Shared memory state - counter: " << data->counter 
              << ", last_target: " << (data->last_target == 0 ? "C" : "D")
              << ", message history: [";
    for (size_t i = 0; i < data->message_history.size(); ++i) {
      std::cout << data->message_history[i];
      if (i < data->message_history.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    
    // Determine target using hash function
    int target = request->id() % 2;  // 0 for C, 1 for D
    
    // Get target address from config
    const auto& edges = config_["edges"];
    const auto& target_edge = edges[target];
    std::string addr = target_edge["ip"].get<std::string>() + ":" + 
                      std::to_string(target_edge["port"].get<int>());
    std::string target_name = target_edge["id"].get<std::string>();

    std::cout << "NodeB: Forwarding data ID " << request->id() 
              << " to " << target_name << " at " << addr << std::endl;

    // Forward data
    auto channel = CreateChannel(addr, grpc::InsecureChannelCredentials());
    DataServiceClient client(channel);
    client.PushData(*request);

    return Status::OK;
  }

 private:
  json config_;
  std::unique_ptr<shared_memory_object> segment_;
  std::unique_ptr<mapped_region> region_;
  SharedData* shared_data_;
  std::unique_ptr<named_mutex> mutex_;

  bool initializeSharedMemory() {
    try {
      // Get real user info (even when running as sudo)
      uid_t real_uid = getuid();
      uid_t effective_uid = geteuid();
      struct passwd *pw = getpwuid(real_uid);
      if (!pw) {
        std::cerr << "Error getting user info: " << strerror(errno) << std::endl;
        return false;
      }

      // Create base directory if it doesn't exist
      const char* base_dir = "/tmp/grpc_shared";
      struct stat st = {0};
      if (stat(base_dir, &st) == -1) {
        if (mkdir(base_dir, 0777) == -1) {
          std::cerr << "Error creating base directory: " << strerror(errno) << std::endl;
          return false;
        }
        // Set permissions
        if (chmod(base_dir, 0777) == -1) {
          std::cerr << "Error setting base directory permissions: " << strerror(errno) << std::endl;
          return false;
        }
      }

      // Create user-specific directory
      std::string user_dir = std::string(base_dir) + "/" + pw->pw_name;
      if (stat(user_dir.c_str(), &st) == -1) {
        if (mkdir(user_dir.c_str(), 0777) == -1) {
          std::cerr << "Error creating user directory: " << strerror(errno) << std::endl;
          return false;
        }
        // Set ownership and permissions
        if (chmod(user_dir.c_str(), 0777) == -1) {
          std::cerr << "Error setting user directory permissions: " << strerror(errno) << std::endl;
          return false;
        }
        if (chown(user_dir.c_str(), real_uid, pw->pw_gid) == -1) {
          std::cerr << "Error setting user directory ownership: " << strerror(errno) << std::endl;
          return false;
        }
      }

      // Remove any existing shared memory
      std::string shm_name = std::string("/") + pw->pw_name + "_counter";
      std::string mutex_name = std::string("/") + pw->pw_name + "_mutex";
      shared_memory_object::remove(shm_name.c_str());
      named_mutex::remove(mutex_name.c_str());

      // Create and map the shared memory segment
      segment_ = std::make_unique<shared_memory_object>(
        create_only,
        shm_name.c_str(),
        read_write
      );
      segment_->truncate(sizeof(SharedData));
      
      // Set permissions for shared memory
      struct stat shm_stat;
      std::string shm_path = std::string("/dev/shm") + shm_name;
      if (stat(shm_path.c_str(), &shm_stat) == 0) {
        if (chmod(shm_path.c_str(), 0666) == -1) {
          std::cerr << "Error setting shared memory permissions: " << strerror(errno) << std::endl;
          return false;
        }
      }
      
      region_ = std::make_unique<mapped_region>(*segment_, read_write);
      shared_data_ = new (region_->get_address()) SharedData();
      shared_data_->counter = 0;
      shared_data_->last_target = -1;
      
      // Create the mutex for synchronization
      mutex_ = std::make_unique<named_mutex>(
        create_only,
        mutex_name.c_str()
      );
      
      std::cout << "Shared memory initialized successfully at " << shm_path << std::endl;
      std::cout << "Running as uid: " << effective_uid << ", real uid: " << real_uid << std::endl;
      return true;
    } catch (const interprocess_exception& ex) {
      std::cerr << "Error initializing shared memory: " << ex.what() << std::endl;
      return false;
    } catch (const std::exception& ex) {
      std::cerr << "Error: " << ex.what() << std::endl;
      return false;
    }
  }
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