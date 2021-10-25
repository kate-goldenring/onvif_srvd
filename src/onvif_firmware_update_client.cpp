#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include "smacros.h"
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
// #ifdef BAZEL_BUILD
// #include "examples/protos/onvif_firmware_update.grpc.pb.h"
// #else
#include "onvif_firmware_update.grpc.pb.h"
// #endif

#include "onvif_firmware_update_client.h" 

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using onvif_firmware_update::FirmwareUpdate;
using onvif_firmware_update::UpdateFirmwareRequest;
using onvif_firmware_update::UpdateFirmwareReply;

FirmwareUpdateClient::FirmwareUpdateClient(std::shared_ptr<Channel> channel)
      : stub_(FirmwareUpdate::NewStub(channel)) {}
FirmwareUpdateClient::FirmwareUpdateClient()
      : stub_(FirmwareUpdate::NewStub(grpc::CreateChannel("localhost:6052",
                          grpc::InsecureChannelCredentials()))) {}

// TODO: return std::string and throw exceptions
bool FirmwareUpdateClient::RequestFirmwareUpdate(std::string& requested_version, std::string& response_version) {
    ClientContext context;
    int reboot_time_secs = 0;
    UpdateFirmwareRequest request;
    request.set_reboot_time_secs(reboot_time_secs);
    request.set_version(requested_version);
    UpdateFirmwareReply reply;
    Status status = stub_->UpdateFirmware(&context, request, &reply);
    if (status.ok()) {
      DEBUG_MSG("Successfull upgraded to version : %s\n", reply.version());
      return true;
    }
    else {
       DEBUG_MSG("UpdateFirmware rpc failed.");
      std::cout << "UpdateFirmware rpc failed." << std::endl;
      return false;
    }
}
  
const float kCoordFactor_ = 10000000.0;
std::unique_ptr<FirmwareUpdate::Stub> stub_;



// std::string requestFirmwareUpgrade(std::string& requested_version) {
//   FirmwareUpdateClient client(
//       grpc::CreateChannel("localhost:6052",
//                           grpc::InsecureChannelCredentials()));                          
//   if client.RequestFirmwareUpdate(requested_version) {
//     return requested_version;
//   } else {
//     throw std::runtime_error("A problem occurred when upgrading firmware");
//   }
// }