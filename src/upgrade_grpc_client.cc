#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include "helper.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#ifdef BAZEL_BUILD
#include "examples/protos/onvif_firmware_update.grpc.pb.h"
#else
#include "onvif_firmware_update.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using onvif_firmware_update::UpdateFirmwareRequest;
using onvif_firmware_update::UpdateFirmware;

class FirmwareUpdateClient {
 public:
  FirmwareUpdateClient(std::shared_ptr<Channel> channel, const std::string& db)
      : stub_(FirmwareUpdate::NewStub(channel)) {
    routeguide::ParseDb(db, &feature_list_);
  }

 private:
  std::string RequestFirmwareUpdate(std::string& requested_version, std::string& response_version) {
    ClientContext context;
    int reboot_time_secs = 0;
    Status status = stub_->UpdateFirmware(&context, version, reboot_time_secs, response_version);
    if (!status.ok()) {
      std::cout << "UpdateFirmware rpc failed." << std::endl;
      return false;
    }
    if (!response_version->version()) {
      std::cout << "Server returns incomplete reply." << std::endl;
      return false;
    }
    return true;
  }

  const float kCoordFactor_ = 10000000.0;
  std::unique_ptr<FirmwareUpdate::Stub> stub_;
}