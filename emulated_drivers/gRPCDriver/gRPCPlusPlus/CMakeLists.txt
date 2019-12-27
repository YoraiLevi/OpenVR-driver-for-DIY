# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ helloworld example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building helloworld.

cmake_minimum_required(VERSION 3.5.1)

project(gRPCPlusPlus C CXX)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  add_definitions(-D_WIN32_WINNT=0x600)
endif()

#Setting up Protobuf and gRPC references
if(GRPC_AS_SUBMODULE)
  # One way to build a projects that uses gRPC is to just include the
  # entire gRPC project tree via "add_subdirectory".
  # This approach is very simple to use, but the are some potential
  # disadvantages:
  # * it includes gRPC's CMakeLists.txt directly into your build script
  #   without and that can make gRPC's internal setting interfere with your
  #   own build.
  # * depending on what's installed on your system, the contents of submodules
  #   in gRPC's third_party/* might need to be available (and there might be
  #   additional prerequisites required to build them). Consider using
  #   the gRPC_*_PROVIDER options to fine-tune the expected behavior.
  #
  # A more robust approach to add dependency on gRPC is using
  # cmake's ExternalProject_Add (see cmake_externalproject/CMakeLists.txt).
  
  # Include the gRPC's cmake build (normally grpc source code would live
  # in a git submodule called "third_party/grpc", but this example lives in
  # the same repository as gRPC sources, so we just look a few directories up)
  add_subdirectory(../../.. ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)
  message(STATUS "Using gRPC via add_subdirectory.")
  
  # After using add_subdirectory, we can now use the grpc targets directly from
  # this build.
  set(_PROTOBUF_LIBPROTOBUF libprotobuf)
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
  set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
else()
  # This branch assumes that gRPC and all its dependencies are already installed
  # on this system, so they can be located by find_package().

  # Find Protobuf installation
  # Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
  set(protobuf_MODULE_COMPATIBLE TRUE)
  find_package(Protobuf CONFIG REQUIRED)
  message(STATUS "Using protobuf ${protobuf_VERSION}")

  set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

  # Find gRPC installation
  # Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
  find_package(gRPC CONFIG REQUIRED)
  message(STATUS "Using gRPC ${gRPC_VERSION}")

  set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()


# Proto file
set(proto_root "../proto/")
get_filename_component(proto_root_path "${proto_root}" ABSOLUTE)

set(PROTOS inputemulation.proto ping.proto pose.proto)
# Generated sources
foreach(_proto ${PROTOS})
    get_filename_component (_proto_path "${proto_root_path}/${_proto}" ABSOLUTE)
    get_filename_component (_proto_NAME_WE "${proto_root_path}/${_proto}" NAME_WE)
    set(proto_src "${CMAKE_SOURCE_DIR}/grpc/${_proto_NAME_WE}.pb.cc")
    set(proto_hdr "${CMAKE_SOURCE_DIR}/grpc/${_proto_NAME_WE}.pb.h")
    set(grpc_src "${CMAKE_SOURCE_DIR}/grpc/${_proto_NAME_WE}.grpc.pb.cc")
    set(grpc_hdr "${CMAKE_SOURCE_DIR}/grpc/${_proto_NAME_WE}.grpc.pb.h")
    list(APPEND proto_srcs ${proto_src})
    list(APPEND proto_hdrs ${proto_hdr})
    list(APPEND grpc_srcs ${grpc_src})
    list(APPEND grpc_hdrs ${grpc_hdr})


    #Compile with Protoc
    add_custom_command(
          OUTPUT "${proto_src}" "${proto_hdr}" "${grpc_src}" "${grpc_hdr}"
          COMMAND ${_PROTOBUF_PROTOC}
          ARGS --grpc_out="${CMAKE_SOURCE_DIR}/grpc"
            --cpp_out="${CMAKE_SOURCE_DIR}/grpc"
            -I "${proto_root_path}"
            -I "${Protobuf_INCLUDE_DIRS}"
            --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
            "${_proto}"
          DEPENDS "${_proto_path}")
endforeach()

# Include generated *.pb.h files
include_directories("${CMAKE_SOURCE_DIR}/grpc")

#include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(GRPC_OUT INTERFACE)
target_sources(GRPC_OUT INTERFACE ${proto_srcs} ${grpc_srcs})
target_link_libraries(GRPC_OUT INTERFACE
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF})

get_filename_component(szevent "CppEvent/szevent.h" ABSOLUTE)
add_library(CPP_EVENT INTERFACE)
target_sources(CPP_EVENT INTERFACE ${szevent})

add_library(gRPCPlusPlus STATIC src/InputEmulationClientImpl.cpp src/InputEmulationServiceImpl.cpp)
target_include_directories (gRPCPlusPlus PUBLIC headers/)
target_link_libraries(gRPCPlusPlus GRPC_OUT CPP_EVENT)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_executable(inputemulation_test debug/main.cc)
  target_link_libraries(inputemulation_test gRPCPlusPlus)
endif()