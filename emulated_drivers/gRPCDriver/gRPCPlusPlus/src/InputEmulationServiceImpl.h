#pragma once
#include "../grpc/inputemulation.grpc.pb.h"
#include "../CppEvent/szevent.h"
namespace gRPCServices {
	class InputEmulationServiceImpl final : public InputEmulation::Service {

	public:
		sz::event<const ::gRPCServices::AttachMessage&> Attached;
		sz::event<const ::gRPCServices::DetachMessage&> Detached;
		sz::event<const ::gRPCServices::TransformMessage&> Transformed;
		InputEmulationServiceImpl() : InputEmulation::Service() {};
		::grpc::Status Attach(::grpc::ServerContext* context, const ::gRPCServices::AttachMessage* request, ::google::protobuf::Empty* response);
		::grpc::Status Detach(::grpc::ServerContext* context, const ::gRPCServices::DetachMessage* request, ::google::protobuf::Empty* response);
		::grpc::Status Transform(::grpc::ServerContext* context, const ::gRPCServices::TransformMessage* request, ::google::protobuf::Empty* response);
	};
}