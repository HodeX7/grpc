// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: data.proto
#ifndef GRPC_data_2eproto__INCLUDED
#define GRPC_data_2eproto__INCLUDED

#include "data.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>
#include <grpcpp/ports_def.inc>

namespace data {

class DataService final {
 public:
  static constexpr char const* service_full_name() {
    return "data.DataService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status PushData(::grpc::ClientContext* context, const ::data::DataMessage& request, ::data::Empty* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::Empty>> AsyncPushData(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::Empty>>(AsyncPushDataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::Empty>> PrepareAsyncPushData(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::Empty>>(PrepareAsyncPushDataRaw(context, request, cq));
    }
    virtual ::grpc::Status GetSharedState(::grpc::ClientContext* context, const ::data::Empty& request, ::data::SharedState* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::SharedState>> AsyncGetSharedState(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::SharedState>>(AsyncGetSharedStateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::SharedState>> PrepareAsyncGetSharedState(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::data::SharedState>>(PrepareAsyncGetSharedStateRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void PushData(::grpc::ClientContext* context, const ::data::DataMessage* request, ::data::Empty* response, std::function<void(::grpc::Status)>) = 0;
      virtual void PushData(::grpc::ClientContext* context, const ::data::DataMessage* request, ::data::Empty* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void GetSharedState(::grpc::ClientContext* context, const ::data::Empty* request, ::data::SharedState* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetSharedState(::grpc::ClientContext* context, const ::data::Empty* request, ::data::SharedState* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::data::Empty>* AsyncPushDataRaw(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::data::Empty>* PrepareAsyncPushDataRaw(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::data::SharedState>* AsyncGetSharedStateRaw(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::data::SharedState>* PrepareAsyncGetSharedStateRaw(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status PushData(::grpc::ClientContext* context, const ::data::DataMessage& request, ::data::Empty* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::Empty>> AsyncPushData(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::Empty>>(AsyncPushDataRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::Empty>> PrepareAsyncPushData(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::Empty>>(PrepareAsyncPushDataRaw(context, request, cq));
    }
    ::grpc::Status GetSharedState(::grpc::ClientContext* context, const ::data::Empty& request, ::data::SharedState* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::SharedState>> AsyncGetSharedState(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::SharedState>>(AsyncGetSharedStateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::SharedState>> PrepareAsyncGetSharedState(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::data::SharedState>>(PrepareAsyncGetSharedStateRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void PushData(::grpc::ClientContext* context, const ::data::DataMessage* request, ::data::Empty* response, std::function<void(::grpc::Status)>) override;
      void PushData(::grpc::ClientContext* context, const ::data::DataMessage* request, ::data::Empty* response, ::grpc::ClientUnaryReactor* reactor) override;
      void GetSharedState(::grpc::ClientContext* context, const ::data::Empty* request, ::data::SharedState* response, std::function<void(::grpc::Status)>) override;
      void GetSharedState(::grpc::ClientContext* context, const ::data::Empty* request, ::data::SharedState* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::data::Empty>* AsyncPushDataRaw(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::data::Empty>* PrepareAsyncPushDataRaw(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::data::SharedState>* AsyncGetSharedStateRaw(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::data::SharedState>* PrepareAsyncGetSharedStateRaw(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_PushData_;
    const ::grpc::internal::RpcMethod rpcmethod_GetSharedState_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status PushData(::grpc::ServerContext* context, const ::data::DataMessage* request, ::data::Empty* response);
    virtual ::grpc::Status GetSharedState(::grpc::ServerContext* context, const ::data::Empty* request, ::data::SharedState* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_PushData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_PushData() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_PushData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PushData(::grpc::ServerContext* /*context*/, const ::data::DataMessage* /*request*/, ::data::Empty* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPushData(::grpc::ServerContext* context, ::data::DataMessage* request, ::grpc::ServerAsyncResponseWriter< ::data::Empty>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetSharedState : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetSharedState() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_GetSharedState() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSharedState(::grpc::ServerContext* /*context*/, const ::data::Empty* /*request*/, ::data::SharedState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetSharedState(::grpc::ServerContext* context, ::data::Empty* request, ::grpc::ServerAsyncResponseWriter< ::data::SharedState>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_PushData<WithAsyncMethod_GetSharedState<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_PushData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_PushData() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::data::DataMessage, ::data::Empty>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::data::DataMessage* request, ::data::Empty* response) { return this->PushData(context, request, response); }));}
    void SetMessageAllocatorFor_PushData(
        ::grpc::MessageAllocator< ::data::DataMessage, ::data::Empty>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::data::DataMessage, ::data::Empty>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_PushData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PushData(::grpc::ServerContext* /*context*/, const ::data::DataMessage* /*request*/, ::data::Empty* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* PushData(
      ::grpc::CallbackServerContext* /*context*/, const ::data::DataMessage* /*request*/, ::data::Empty* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_GetSharedState : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetSharedState() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::data::Empty, ::data::SharedState>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::data::Empty* request, ::data::SharedState* response) { return this->GetSharedState(context, request, response); }));}
    void SetMessageAllocatorFor_GetSharedState(
        ::grpc::MessageAllocator< ::data::Empty, ::data::SharedState>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::data::Empty, ::data::SharedState>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_GetSharedState() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSharedState(::grpc::ServerContext* /*context*/, const ::data::Empty* /*request*/, ::data::SharedState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetSharedState(
      ::grpc::CallbackServerContext* /*context*/, const ::data::Empty* /*request*/, ::data::SharedState* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_PushData<WithCallbackMethod_GetSharedState<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_PushData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_PushData() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_PushData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PushData(::grpc::ServerContext* /*context*/, const ::data::DataMessage* /*request*/, ::data::Empty* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetSharedState : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetSharedState() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_GetSharedState() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSharedState(::grpc::ServerContext* /*context*/, const ::data::Empty* /*request*/, ::data::SharedState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_PushData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_PushData() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_PushData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PushData(::grpc::ServerContext* /*context*/, const ::data::DataMessage* /*request*/, ::data::Empty* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPushData(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetSharedState : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetSharedState() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_GetSharedState() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSharedState(::grpc::ServerContext* /*context*/, const ::data::Empty* /*request*/, ::data::SharedState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetSharedState(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_PushData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_PushData() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->PushData(context, request, response); }));
    }
    ~WithRawCallbackMethod_PushData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status PushData(::grpc::ServerContext* /*context*/, const ::data::DataMessage* /*request*/, ::data::Empty* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* PushData(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetSharedState : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetSharedState() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetSharedState(context, request, response); }));
    }
    ~WithRawCallbackMethod_GetSharedState() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSharedState(::grpc::ServerContext* /*context*/, const ::data::Empty* /*request*/, ::data::SharedState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetSharedState(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_PushData : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_PushData() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::data::DataMessage, ::data::Empty>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::data::DataMessage, ::data::Empty>* streamer) {
                       return this->StreamedPushData(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_PushData() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status PushData(::grpc::ServerContext* /*context*/, const ::data::DataMessage* /*request*/, ::data::Empty* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPushData(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::data::DataMessage,::data::Empty>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetSharedState : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetSharedState() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::data::Empty, ::data::SharedState>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::data::Empty, ::data::SharedState>* streamer) {
                       return this->StreamedGetSharedState(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetSharedState() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetSharedState(::grpc::ServerContext* /*context*/, const ::data::Empty* /*request*/, ::data::SharedState* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetSharedState(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::data::Empty,::data::SharedState>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_PushData<WithStreamedUnaryMethod_GetSharedState<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_PushData<WithStreamedUnaryMethod_GetSharedState<Service > > StreamedService;
};

}  // namespace data


#include <grpcpp/ports_undef.inc>
#endif  // GRPC_data_2eproto__INCLUDED
