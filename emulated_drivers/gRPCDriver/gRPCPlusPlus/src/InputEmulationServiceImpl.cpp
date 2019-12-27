#include "InputEmulationServiceImpl.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
namespace gRPCServices {
	::grpc::Status InputEmulationServiceImpl::Attach(::grpc::ServerContext* context, const::gRPCServices::AttachMessage* request, ::google::protobuf::Empty* response)
	{
#ifdef _DEBUG
		std::cout << "Attaching:" << "id:" << request->id() << "type:" << request->device();
		std::cout << std::endl;
#endif // _DEBUG
		this->Attached(*request);
		return ::grpc::Status::OK;
	}

	::grpc::Status InputEmulationServiceImpl::Detach(::grpc::ServerContext* context, const::gRPCServices::DetachMessage* request, ::google::protobuf::Empty* response)
	{
#ifdef _DEBUG
		std::cout << "Detaching:" << "id:" << request->id();
		std::cout << std::endl;
#endif // _DEBUG
		this->Detached(*request);
		return ::grpc::Status::OK;
	}

	::grpc::Status InputEmulationServiceImpl::Transform(::grpc::ServerContext* context, const::gRPCServices::TransformMessage* request, ::google::protobuf::Empty* response)
	{
#ifdef _DEBUG
		std::cout << "Transforming:" << "id:" << request->id() << "I am not writing the expansion of this atm";
		std::cout << std::endl;
#endif // _DEBUG
		this->Transformed(*request);
		return ::grpc::Status::OK;
	}
}