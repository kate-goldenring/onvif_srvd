// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: onvif_firmware_update.proto

#include "onvif_firmware_update.pb.h"
#include "onvif_firmware_update.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace onvif_firmware_update {

static const char* FirmwareUpdate_method_names[] = {
  "/onvif_firmware_update.FirmwareUpdate/UpdateFirmware",
};

std::unique_ptr< FirmwareUpdate::Stub> FirmwareUpdate::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< FirmwareUpdate::Stub> stub(new FirmwareUpdate::Stub(channel, options));
  return stub;
}

FirmwareUpdate::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_UpdateFirmware_(FirmwareUpdate_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status FirmwareUpdate::Stub::UpdateFirmware(::grpc::ClientContext* context, const ::onvif_firmware_update::UpdateFirmwareRequest& request, ::onvif_firmware_update::UpdateFirmwareReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::onvif_firmware_update::UpdateFirmwareRequest, ::onvif_firmware_update::UpdateFirmwareReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_UpdateFirmware_, context, request, response);
}

void FirmwareUpdate::Stub::async::UpdateFirmware(::grpc::ClientContext* context, const ::onvif_firmware_update::UpdateFirmwareRequest* request, ::onvif_firmware_update::UpdateFirmwareReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::onvif_firmware_update::UpdateFirmwareRequest, ::onvif_firmware_update::UpdateFirmwareReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateFirmware_, context, request, response, std::move(f));
}

void FirmwareUpdate::Stub::async::UpdateFirmware(::grpc::ClientContext* context, const ::onvif_firmware_update::UpdateFirmwareRequest* request, ::onvif_firmware_update::UpdateFirmwareReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateFirmware_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::onvif_firmware_update::UpdateFirmwareReply>* FirmwareUpdate::Stub::PrepareAsyncUpdateFirmwareRaw(::grpc::ClientContext* context, const ::onvif_firmware_update::UpdateFirmwareRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::onvif_firmware_update::UpdateFirmwareReply, ::onvif_firmware_update::UpdateFirmwareRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_UpdateFirmware_, context, request);
}

::grpc::ClientAsyncResponseReader< ::onvif_firmware_update::UpdateFirmwareReply>* FirmwareUpdate::Stub::AsyncUpdateFirmwareRaw(::grpc::ClientContext* context, const ::onvif_firmware_update::UpdateFirmwareRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncUpdateFirmwareRaw(context, request, cq);
  result->StartCall();
  return result;
}

FirmwareUpdate::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FirmwareUpdate_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< FirmwareUpdate::Service, ::onvif_firmware_update::UpdateFirmwareRequest, ::onvif_firmware_update::UpdateFirmwareReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](FirmwareUpdate::Service* service,
             ::grpc::ServerContext* ctx,
             const ::onvif_firmware_update::UpdateFirmwareRequest* req,
             ::onvif_firmware_update::UpdateFirmwareReply* resp) {
               return service->UpdateFirmware(ctx, req, resp);
             }, this)));
}

FirmwareUpdate::Service::~Service() {
}

::grpc::Status FirmwareUpdate::Service::UpdateFirmware(::grpc::ServerContext* context, const ::onvif_firmware_update::UpdateFirmwareRequest* request, ::onvif_firmware_update::UpdateFirmwareReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace onvif_firmware_update

