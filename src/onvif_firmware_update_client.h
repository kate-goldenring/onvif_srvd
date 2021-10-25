#ifndef FIRMWARE_UPDATE_CLIENT_H
#define FIRMWARE_UPDATE_CLIENT_H


#include <stdint.h>
#include <string>

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

class FirmwareUpdateClient {
    public:
        FirmwareUpdateClient(std::shared_ptr<grpc::Channel> channel);
        FirmwareUpdateClient();
        bool RequestFirmwareUpdate(std::string& requested_version);
    private: 
        const float kCoordFactor_ = 10000000.0;
        std::unique_ptr<FirmwareUpdate::Stub> stub_;
};
#endif // FIRMWARE_UPDATE_CLIENT_H