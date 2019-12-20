#include "ServerDriver.h"
#include "driverlog.h"
using namespace vr;

//vr::EVRInitError CServerDriver::Init(vr::IVRDriverContext* pDriverContext)
//{
//	VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
//	InitDriverLog( vr::VRDriverLog() );
//
//	//m_pNullHmdLatest = new CSampleDeviceDriver();
//	//vr::VRServerDriverHost()->TrackedDeviceAdded(m_pNullHmdLatest->GetSerialNumber().c_str(), vr::TrackedDeviceClass_HMD, m_pNullHmdLatest);
//
//	//m_pController = new CSampleControllerDriver();
//	//m_pController->SetControllerIndex(1);
//	//vr::VRServerDriverHost()->TrackedDeviceAdded(m_pController->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, m_pController);
//
//
//	//m_pController2 = new CSampleControllerDriver();
//	//m_pController2->SetControllerIndex(2);
//	//vr::VRServerDriverHost()->TrackedDeviceAdded(m_pController2->GetSerialNumber().c_str(), vr::TrackedDeviceClass_Controller, m_pController2);
//
//	return vr::VRInitError_None;
//}
//void CServerDriver::Cleanup()
//{
//	CleanupDriverLog();
//	//delete m_pNullHmdLatest;
//	//m_pNullHmdLatest = NULL;
//	//delete m_pController;
//	//m_pController = NULL;
////	delete m_pController2;
////	m_pController2 = NULL;
//}
//void CServerDriver::RunFrame()
//{
////	if (m_pNullHmdLatest)
////	{
////		m_pNullHmdLatest->RunFrame();
////	}
////	if (m_pController)
////	{
////		m_pController->RunFrame();
////	}
////	if (m_pController2)
////	{
////		m_pController2->RunFrame();
//}

EVRInitError CServerDriver::Init(IVRDriverContext* pDriverContext)
{
	return EVRInitError();
}

void CServerDriver::Cleanup()
{
}

const char* const* CServerDriver::GetInterfaceVersions()
{
	return nullptr;
}

void CServerDriver::RunFrame()
{
}

bool CServerDriver::ShouldBlockStandbyMode()
{
	return false;
}

void CServerDriver::EnterStandby()
{
}

void CServerDriver::LeaveStandby()
{
}
