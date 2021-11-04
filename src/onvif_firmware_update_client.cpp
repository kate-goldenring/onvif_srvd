#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include "smacros.h"
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
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

const int DEFAULT_TIMEOUT = 30;

FirmwareUpdateClient::FirmwareUpdateClient(std::shared_ptr<Channel> channel) {
  DEBUG_MSG("Constructing FirmwareUpdateClient\n");
  stub_ = FirmwareUpdate::NewStub(channel);
  DEBUG_MSG("Constructed FirmwareUpdateClient\n");
}
FirmwareUpdateClient::FirmwareUpdateClient() {
  DEBUG_MSG("Constructing FirmwareUpdateClient\n");
  std::string target_str = "localhost:6052";
  stub_ = FirmwareUpdate::NewStub(grpc::CreateChannel("10.137.184.218:6052",
                          grpc::InsecureChannelCredentials()));
}

// TODO: return std::string and throw exceptions
std::string FirmwareUpdateClient::RequestFirmwareUpdate(char * requested_version) {
    DEBUG_MSG("RequestFirmwareUpdate called with version : %s\n", requested_version);
    ClientContext context;
    UpdateFirmwareRequest request;
    request.set_reboot_time_secs(DEFAULT_TIMEOUT);
    request.set_version(requested_version);
    UpdateFirmwareReply reply;
    Status status = stub_->UpdateFirmware(&context, request, &reply);
    if (status.ok()) {
      char* reply_char = const_cast<char*>(reply.version().c_str());
      std::cout << reply_char;
      DEBUG_MSG("Successfull upgraded to version : %s\n", reply_char);
      return reply.version();
    }
    else {
      DEBUG_MSG("UpdateFirmware rpc failed.\n");
      std::cout << "UpdateFirmware rpc failed." << std::endl;
      throw std::invalid_argument( "UpdateFirmware rpc failed." );
    }
}

