cmake_minimum_required(VERSION 3.5.1)

project(OnvifFirmwareUpdate C CXX)

include(./cmake/common.cmake)

# Proto file
get_filename_component(fu_proto "./proto/onvif_firmware_update.proto" ABSOLUTE)
get_filename_component(fu_proto_path "${fu_proto}" PATH)

# Generated sources
set(fu_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/onvif_firmware_update.pb.cc")
set(fu_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/onvif_firmware_update.pb.h")
set(fu_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/onvif_firmware_update.grpc.pb.cc")
set(fu_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/onvif_firmware_update.grpc.pb.h")
add_custom_command(
      OUTPUT "${fu_proto_srcs}" "${fu_proto_hdrs}" "${fu_grpc_srcs}" "${fu_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${fu_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${fu_proto}"
      DEPENDS "${fu_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# fu_grpc_proto
add_library(fu_grpc_proto
  ${fu_grpc_srcs}
  ${fu_grpc_hdrs}
  ${fu_proto_srcs}
  ${fu_proto_hdrs})
target_link_libraries(fu_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

add_executable(firmware_update_client "./src/onvif_firmware_update_client.cpp")
target_link_libraries(firmware_update_client
  fu_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})