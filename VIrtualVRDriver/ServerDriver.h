#pragma once
#include <openvr_driver.h>

class CServerDriver : public vr::IServerTrackedDeviceProvider
{
public:
	// Inherited via IServerTrackedDeviceProvider
	virtual EVRInitError Init(IVRDriverContext* pDriverContext) override;
	virtual void Cleanup() override;
	virtual const char* const* GetInterfaceVersions() override;
	virtual void RunFrame() override;
	virtual bool ShouldBlockStandbyMode() override;
	virtual void EnterStandby() override;
	virtual void LeaveStandby() override;
private:

	//IDK YET
//private:
//	CSampleDeviceDriver* m_pNullHmdLatest = nullptr;
//	CSampleControllerDriver* m_pController = nullptr;
//	CSampleControllerDriver* m_pController2 = nullptr;
};

//
//	/*vr::VREvent_t vrEvent;
//	while ( vr::VRServerDriverHost()->PollNextEvent( &vrEvent, sizeof( vrEvent ) ) )
//	{
//		if ( m_pController )
//		{
//			m_pController->ProcessEvent( vrEvent );
//		}
//	}*/