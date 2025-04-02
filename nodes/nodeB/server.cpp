//NODE B
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
#include <map>
#include <thread>

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
    std::vector<int> recent_ids;  // Changed from message_history to recent_ids
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
  DataServiceImpl(const nlohmann::json& config) : shared_data_(nullptr) {
    // Initialize edges from config
    for (const auto& edge : config["edges"]) {
      std::string id = edge["id"].get<std::string>();
      std::string address = edge["ip"].get<std::string>() + ":" + std::to_string(edge["port"].get<int>());
      edges_[id] = address;
    }

    // Initialize shared memory
    try {
      if (!initializeSharedMemory()) {
        throw std::runtime_error("Failed to initialize shared memory");
      }
    } catch (const std::exception& e) {
      std::cerr << "Error initializing shared memory: " << e.what() << std::endl;
      throw;
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

  Status PushData(ServerContext* context, const data::DataMessage* request, data::Empty* response) override {
    try {
      // Get shared data with mutex lock
      std::lock_guard<boost::interprocess::named_mutex> lock(*mutex_);
      
      // Determine target node based on data ID
      int target = request->id() % 2; // 0 → C, 1 → D
      std::string target_address = (target == 0) ? edges_["C"] : edges_["D"];
      
      // Create channel and stub for target node
      auto channel = grpc::CreateChannel(target_address, grpc::InsecureChannelCredentials());
      auto stub = data::DataService::NewStub(channel);
      
      // Forward data to target node with retry logic
        const int max_retries = 3; // Set the maximum number of retries
        for (int attempt = 0; attempt < max_retries; ++attempt) {
            grpc::ClientContext client_context;
            data::Empty forward_response;
            Status status = stub->PushData(&client_context, *request, &forward_response);
            
            if (status.ok()) {
                // Successfully forwarded data
                break; // Exit the retry loop
            } else {
                std::cerr << "Attempt " << (attempt + 1) << " failed to forward data to " << target_address 
                          << ": " << status.error_message() << std::endl;
                // Optionally, you can add a delay before retrying
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Delay before retrying
            }
        }
      
      // Update shared memory state
      shared_data_->counter++;
      shared_data_->last_target = target;
      shared_data_->recent_ids.push_back(request->id());
      
      // Keep only the last 10 messages
      if (shared_data_->recent_ids.size() > 10) {
        shared_data_->recent_ids.erase(shared_data_->recent_ids.begin());
      }
      
      // Log the state
      std::cout << "NodeB: Shared memory state - counter: " << shared_data_->counter 
                << ", last_target: " << target_address
                << ", recent IDs: [";
      for (size_t i = 0; i < shared_data_->recent_ids.size(); ++i) {
        std::cout << shared_data_->recent_ids[i];
        if (i < shared_data_->recent_ids.size() - 1) std::cout << ", ";
      }
      std::cout << "]" << std::endl;
      
      std::cout << "NodeB: Forwarding ID " << request->id() << " to " << target_address << "\n";
      
      return Status::OK;
    } catch (const std::exception& e) {
      std::cerr << "Error in PushData: " << e.what() << std::endl;
      return Status(grpc::INTERNAL, "Internal server error");
    }
  }

  Status GetSharedState(ServerContext* context, const data::Empty* request, data::SharedState* response) override {
    std::lock_guard<boost::interprocess::named_mutex> lock(*mutex_);
    response->set_counter(shared_data_->counter);
    response->set_last_target(shared_data_->last_target);
    for (const auto& id : shared_data_->recent_ids) {
        response->add_recent_ids(id);
    }
    return Status::OK;
  }

 private:
  json config_;
  std::unique_ptr<shared_memory_object> segment_;
  std::unique_ptr<mapped_region> region_;
  std::unique_ptr<named_mutex> mutex_;
  SharedData* shared_data_;
  std::map<std::string, std::string> edges_;

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