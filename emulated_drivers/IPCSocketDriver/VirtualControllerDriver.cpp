#include "VirtualControllerDriver.h"
using namespace vr;

EVRInitError CVirtualControllerDriver::Activate(uint32_t unObjectId)
{
	return EVRInitError();
}

void CVirtualControllerDriver::Deactivate()
{
}

void CVirtualControllerDriver::EnterStandby()
{
}

void* CVirtualControllerDriver::GetComponent(const char* pchComponentNameAndVersion)
{
	return nullptr;
}

void CVirtualControllerDriver::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
{
}

DriverPose_t CVirtualControllerDriver::GetPose()
{
	return DriverPose_t();
}
