// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: data.proto

#include "data.pb.h"
#include "data.grpc.pb.h"

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
namespace data {

static const char* DataService_method_names[] = {
  "/data.DataService/PushData",
  "/data.DataService/GetSharedState",
};

std::unique_ptr< DataService::Stub> DataService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DataService::Stub> stub(new DataService::Stub(channel, options));
  return stub;
}

DataService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_PushData_(DataService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetSharedState_(DataService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DataService::Stub::PushData(::grpc::ClientContext* context, const ::data::DataMessage& request, ::data::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::data::DataMessage, ::data::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_PushData_, context, request, response);
}

void DataService::Stub::async::PushData(::grpc::ClientContext* context, const ::data::DataMessage* request, ::data::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::data::DataMessage, ::data::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_PushData_, context, request, response, std::move(f));
}

void DataService::Stub::async::PushData(::grpc::ClientContext* context, const ::data::DataMessage* request, ::data::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_PushData_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::data::Empty>* DataService::Stub::PrepareAsyncPushDataRaw(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::data::Empty, ::data::DataMessage, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_PushData_, context, request);
}

::grpc::ClientAsyncResponseReader< ::data::Empty>* DataService::Stub::AsyncPushDataRaw(::grpc::ClientContext* context, const ::data::DataMessage& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncPushDataRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status DataService::Stub::GetSharedState(::grpc::ClientContext* context, const ::data::Empty& request, ::data::SharedState* response) {
  return ::grpc::internal::BlockingUnaryCall< ::data::Empty, ::data::SharedState, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetSharedState_, context, request, response);
}

void DataService::Stub::async::GetSharedState(::grpc::ClientContext* context, const ::data::Empty* request, ::data::SharedState* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::data::Empty, ::data::SharedState, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetSharedState_, context, request, response, std::move(f));
}

void DataService::Stub::async::GetSharedState(::grpc::ClientContext* context, const ::data::Empty* request, ::data::SharedState* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetSharedState_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::data::SharedState>* DataService::Stub::PrepareAsyncGetSharedStateRaw(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::data::SharedState, ::data::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetSharedState_, context, request);
}

::grpc::ClientAsyncResponseReader< ::data::SharedState>* DataService::Stub::AsyncGetSharedStateRaw(::grpc::ClientContext* context, const ::data::Empty& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetSharedStateRaw(context, request, cq);
  result->StartCall();
  return result;
}

DataService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::data::DataMessage, ::data::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::data::DataMessage* req,
             ::data::Empty* resp) {
               return service->PushData(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::data::Empty, ::data::SharedState, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::data::Empty* req,
             ::data::SharedState* resp) {
               return service->GetSharedState(ctx, req, resp);
             }, this)));
}

DataService::Service::~Service() {
}

::grpc::Status DataService::Service::PushData(::grpc::ServerContext* context, const ::data::DataMessage* request, ::data::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::GetSharedState(::grpc::ServerContext* context, const ::data::Empty* request, ::data::SharedState* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace data

