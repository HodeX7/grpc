// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: hello.proto

#include "hello.pb.h"
#include "hello.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace hello {

static const char* HelloService_method_names[] = {
  "/hello.HelloService/SayHello",
};

std::unique_ptr< HelloService::Stub> HelloService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< HelloService::Stub> stub(new HelloService::Stub(channel, options));
  return stub;
}

HelloService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SayHello_(HelloService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status HelloService::Stub::SayHello(::grpc::ClientContext* context, const ::hello::HelloRequest& request, ::hello::HelloReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::hello::HelloRequest, ::hello::HelloReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SayHello_, context, request, response);
}

void HelloService::Stub::async::SayHello(::grpc::ClientContext* context, const ::hello::HelloRequest* request, ::hello::HelloReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::hello::HelloRequest, ::hello::HelloReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SayHello_, context, request, response, std::move(f));
}

void HelloService::Stub::async::SayHello(::grpc::ClientContext* context, const ::hello::HelloRequest* request, ::hello::HelloReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SayHello_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::hello::HelloReply>* HelloService::Stub::PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, const ::hello::HelloRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::hello::HelloReply, ::hello::HelloRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SayHello_, context, request);
}

::grpc::ClientAsyncResponseReader< ::hello::HelloReply>* HelloService::Stub::AsyncSayHelloRaw(::grpc::ClientContext* context, const ::hello::HelloRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSayHelloRaw(context, request, cq);
  result->StartCall();
  return result;
}

HelloService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      HelloService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< HelloService::Service, ::hello::HelloRequest, ::hello::HelloReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](HelloService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::hello::HelloRequest* req,
             ::hello::HelloReply* resp) {
               return service->SayHello(ctx, req, resp);
             }, this)));
}

HelloService::Service::~Service() {
}

::grpc::Status HelloService::Service::SayHello(::grpc::ServerContext* context, const ::hello::HelloRequest* request, ::hello::HelloReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace hello

