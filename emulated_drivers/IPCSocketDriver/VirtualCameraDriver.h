#pragma once
#include <openvr_driver.h>
class CVirtualCameraDriver : public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent
{
public:
	CVirtualCameraDriver();
	virtual ~CVirtualCameraDriver();
	void RunFrame();

	// Inherited via ITrackedDeviceServerDriver
	virtual vr::EVRInitError Activate(uint32_t unObjectId) override;
	virtual void Deactivate() override;
	virtual void EnterStandby() override;
	virtual void* GetComponent(const char* pchComponentNameAndVersion) override;
	virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
	virtual vr::DriverPose_t GetPose() override;

	// Inherited via IVRDisplayComponent
	virtual void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
	virtual bool IsDisplayOnDesktop() override;
	virtual bool IsDisplayRealDisplay() override;
	virtual void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	virtual void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
	virtual void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	virtual vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;

private:
	vr::TrackedDeviceIndex_t m_unObjectId;
};

inline vr::HmdQuaternion_t HmdQuaternion_Init(double w, double x, double y, double z)
{
	vr::HmdQuaternion_t quat;
	quat.w = w;
	quat.x = x;
	quat.y = y;
	quat.z = z;
	return quat;
}

inline void HmdMatrix_SetIdentity(vr::HmdMatrix34_t* pMatrix)
{
	pMatrix->m[0][0] = 1.f;
	pMatrix->m[0][1] = 0.f;
	pMatrix->m[0][2] = 0.f;
	pMatrix->m[0][3] = 0.f;
	pMatrix->m[1][0] = 0.f;
	pMatrix->m[1][1] = 1.f;
	pMatrix->m[1][2] = 0.f;
	pMatrix->m[1][3] = 0.f;
	pMatrix->m[2][0] = 0.f;
	pMatrix->m[2][1] = 0.f;
	pMatrix->m[2][2] = 1.f;
	pMatrix->m[2][3] = 0.f;
}


//class CSampleDeviceDriver : public vr::ITrackedDeviceServerDriver, public vr::IVRDisplayComponent
//{
//public:
//	CSampleDeviceDriver()
//	{
//		m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
//		m_ulPropertyContainer = vr::k_ulInvalidPropertyContainer;
//
//		//DriverLog( "Using settings values\n" );
//		m_flIPD = vr::VRSettings()->GetFloat(k_pch_SteamVR_Section, k_pch_SteamVR_IPD_Float);
//
//		char buf[1024];
//		vr::VRSettings()->GetString(k_pch_Sample_Section, k_pch_Sample_SerialNumber_String, buf, sizeof(buf));
//		m_sSerialNumber = buf;
//
//		vr::VRSettings()->GetString(k_pch_Sample_Section, k_pch_Sample_ModelNumber_String, buf, sizeof(buf));
//		m_sModelNumber = buf;
//
//		m_nWindowX = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowX_Int32);
//		m_nWindowY = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowY_Int32);
//		m_nWindowWidth = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowWidth_Int32);
//		m_nWindowHeight = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_WindowHeight_Int32);
//		m_nRenderWidth = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_RenderWidth_Int32);
//		m_nRenderHeight = vr::VRSettings()->GetInt32(k_pch_Sample_Section, k_pch_Sample_RenderHeight_Int32);
//		m_flSecondsFromVsyncToPhotons = vr::VRSettings()->GetFloat(k_pch_Sample_Section, k_pch_Sample_SecondsFromVsyncToPhotons_Float);
//		m_flDisplayFrequency = vr::VRSettings()->GetFloat(k_pch_Sample_Section, k_pch_Sample_DisplayFrequency_Float);
//
//		/*DriverLog( "driver_null: Serial Number: %s\n", m_sSerialNumber.c_str() );
//		DriverLog( "driver_null: Model Number: %s\n", m_sModelNumber.c_str() );
//		DriverLog( "driver_null: Window: %d %d %d %d\n", m_nWindowX, m_nWindowY, m_nWindowWidth, m_nWindowHeight );
//		DriverLog( "driver_null: Render Target: %d %d\n", m_nRenderWidth, m_nRenderHeight );
//		DriverLog( "driver_null: Seconds from Vsync to Photons: %f\n", m_flSecondsFromVsyncToPhotons );
//		DriverLog( "driver_null: Display Frequency: %f\n", m_flDisplayFrequency );
//		DriverLog( "driver_null: IPD: %f\n", m_flIPD );*/
//	}
//
//	virtual ~CSampleDeviceDriver()
//	{
//	}
//
//
//	virtual EVRInitError Activate(vr::TrackedDeviceIndex_t unObjectId)
//	{
//		m_unObjectId = unObjectId;
//		m_ulPropertyContainer = vr::VRProperties()->TrackedDeviceToPropertyContainer(m_unObjectId);
//
//
//		vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_ModelNumber_String, m_sModelNumber.c_str());
//		vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, Prop_RenderModelName_String, m_sModelNumber.c_str());
//		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_UserIpdMeters_Float, m_flIPD);
//		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_UserHeadToEyeDepthMeters_Float, 0.f);
//		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_DisplayFrequency_Float, m_flDisplayFrequency);
//		vr::VRProperties()->SetFloatProperty(m_ulPropertyContainer, Prop_SecondsFromVsyncToPhotons_Float, m_flSecondsFromVsyncToPhotons);
//
//		// return a constant that's not 0 (invalid) or 1 (reserved for Oculus)
//		vr::VRProperties()->SetUint64Property(m_ulPropertyContainer, Prop_CurrentUniverseId_Uint64, 2);
//
//		// avoid "not fullscreen" warnings from vrmonitor
//		vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, Prop_IsOnDesktop_Bool, false);
//
//		//Debug mode activate Windowed Mode (borderless fullscreen), locked to 30 FPS, for testing
//		vr::VRProperties()->SetBoolProperty(m_ulPropertyContainer, Prop_DisplayDebugMode_Bool, true);
//
//		// Icons can be configured in code or automatically configured by an external file "drivername\resources\driver.vrresources".
//		// Icon properties NOT configured in code (post Activate) are then auto-configured by the optional presence of a driver's "drivername\resources\driver.vrresources".
//		// In this manner a driver can configure their icons in a flexible data driven fashion by using an external file.
//		//
//		// The structure of the driver.vrresources file allows a driver to specialize their icons based on their HW.
//		// Keys matching the value in "Prop_ModelNumber_String" are considered first, since the driver may have model specific icons.
//		// An absence of a matching "Prop_ModelNumber_String" then considers the ETrackedDeviceClass ("HMD", "Controller", "GenericTracker", "TrackingReference")
//		// since the driver may have specialized icons based on those device class names.
//		//
//		// An absence of either then falls back to the "system.vrresources" where generic device class icons are then supplied.
//		//
//		// Please refer to "bin\drivers\sample\resources\driver.vrresources" which contains this sample configuration.
//		//
//		// "Alias" is a reserved key and specifies chaining to another json block.
//		//
//		// In this sample configuration file (overly complex FOR EXAMPLE PURPOSES ONLY)....
//		//
//		// "Model-v2.0" chains through the alias to "Model-v1.0" which chains through the alias to "Model-v Defaults".
//		//
//		// Keys NOT found in "Model-v2.0" would then chase through the "Alias" to be resolved in "Model-v1.0" and either resolve their or continue through the alias.
//		// Thus "Prop_NamedIconPathDeviceAlertLow_String" in each model's block represent a specialization specific for that "model".
//		// Keys in "Model-v Defaults" are an example of mapping to the same states, and here all map to "Prop_NamedIconPathDeviceOff_String".
//		//
//		bool bSetupIconUsingExternalResourceFile = true;
//		if (!bSetupIconUsingExternalResourceFile)
//		{
//			// Setup properties directly in code.
//			// Path values are of the form {drivername}\icons\some_icon_filename.png
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceOff_String, "{null}/icons/headset_sample_status_off.png");
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceSearching_String, "{null}/icons/headset_sample_status_searching.gif");
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceSearchingAlert_String, "{null}/icons/headset_sample_status_searching_alert.gif");
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceReady_String, "{null}/icons/headset_sample_status_ready.png");
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceReadyAlert_String, "{null}/icons/headset_sample_status_ready_alert.png");
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceNotReady_String, "{null}/icons/headset_sample_status_error.png");
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceStandby_String, "{null}/icons/headset_sample_status_standby.png");
//			vr::VRProperties()->SetStringProperty(m_ulPropertyContainer, vr::Prop_NamedIconPathDeviceAlertLow_String, "{null}/icons/headset_sample_status_ready_low.png");
//		}
//
//		return VRInitError_None;
//	}
//
//	virtual void Deactivate()
//	{
//		m_unObjectId = vr::k_unTrackedDeviceIndexInvalid;
//	}
//
//	virtual void EnterStandby()
//	{
//	}
//
//	void* GetComponent(const char* pchComponentNameAndVersion)
//	{
//		if (!_stricmp(pchComponentNameAndVersion, vr::IVRDisplayComponent_Version))
//		{
//			return (vr::IVRDisplayComponent*)this;
//		}
//
//		// override this to add a component to a driver
//		return NULL;
//	}
//
//	virtual void PowerOff()
//	{
//	}
//
//	/** debug request from a client */
//	virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
//	{
//		if (unResponseBufferSize >= 1)
//			pchResponseBuffer[0] = 0;
//	}
//
//	virtual void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
//	{
//		*pnX = m_nWindowX;
//		*pnY = m_nWindowY;
//		*pnWidth = m_nWindowWidth;
//		*pnHeight = m_nWindowHeight;
//	}
//
//	virtual bool IsDisplayOnDesktop()
//	{
//		return true;
//	}
//
//	virtual bool IsDisplayRealDisplay()
//	{
//		return false;
//	}
//
//	virtual void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight)
//	{
//		*pnWidth = m_nRenderWidth;
//		*pnHeight = m_nRenderHeight;
//	}
//
//	virtual void GetEyeOutputViewport(EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
//	{
//		*pnY = 0;
//		*pnWidth = m_nWindowWidth / 2;
//		*pnHeight = m_nWindowHeight;
//
//		if (eEye == Eye_Left)
//		{
//			*pnX = 0;
//		}
//		else
//		{
//			*pnX = m_nWindowWidth / 2;
//		}
//	}
//
//	virtual void GetProjectionRaw(EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
//	{
//		*pfLeft = -1.0;
//		*pfRight = 1.0;
//		*pfTop = -1.0;
//		*pfBottom = 1.0;
//	}
//
//	virtual DistortionCoordinates_t ComputeDistortion(EVREye eEye, float fU, float fV)
//	{
//		DistortionCoordinates_t coordinates;
//		coordinates.rfBlue[0] = fU;
//		coordinates.rfBlue[1] = fV;
//		coordinates.rfGreen[0] = fU;
//		coordinates.rfGreen[1] = fV;
//		coordinates.rfRed[0] = fU;
//		coordinates.rfRed[1] = fV;
//		return coordinates;
//	}
//
//	virtual DriverPose_t GetPose()
//	{
//		DriverPose_t pose = { 0 };
//		pose.poseIsValid = true;
//		pose.result = TrackingResult_Running_OK;
//		pose.deviceIsConnected = true;
//
//		pose.qWorldFromDriverRotation = HmdQuaternion_Init(1, 0, 0, 0);
//		pose.qDriverFromHeadRotation = HmdQuaternion_Init(1, 0, 0, 0);
//
//		//Simple change yaw, pitch, roll with numpad keys
//		if ((GetAsyncKeyState(VK_NUMPAD3) & 0x8000) != 0) yaw += 0.01;
//		if ((GetAsyncKeyState(VK_NUMPAD1) & 0x8000) != 0) yaw += -0.01;
//
//		if ((GetAsyncKeyState(VK_NUMPAD4) & 0x8000) != 0) pitch += 0.01;
//		if ((GetAsyncKeyState(VK_NUMPAD6) & 0x8000) != 0) pitch += -0.01;
//
//		if ((GetAsyncKeyState(VK_NUMPAD8) & 0x8000) != 0) roll += 0.01;
//		if ((GetAsyncKeyState(VK_NUMPAD2) & 0x8000) != 0) roll += -0.01;
//
//		if ((GetAsyncKeyState(VK_NUMPAD9) & 0x8000) != 0)
//		{
//			yaw = 0;
//			pitch = 0;
//			roll = 0;
//		}
//
//		if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0) pZ += -0.01;
//		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0) pZ += 0.01;
//
//		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) pX += -0.01;
//		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) pX += 0.01;
//
//		if ((GetAsyncKeyState(VK_PRIOR) & 0x8000) != 0) pY += 0.01;
//		if ((GetAsyncKeyState(VK_NEXT) & 0x8000) != 0) pY += -0.01;
//
//		if ((GetAsyncKeyState(VK_END) & 0x8000) != 0) { pX = 0; pY = 0; pZ = 0; }
//
//		pose.vecPosition[0] = pX;
//		pose.vecPosition[1] = pY;
//		pose.vecPosition[2] = pZ;
//
//		//Convert yaw, pitch, roll to quaternion
//		t0 = cos(yaw * 0.5);
//		t1 = sin(yaw * 0.5);
//		t2 = cos(roll * 0.5);
//		t3 = sin(roll * 0.5);
//		t4 = cos(pitch * 0.5);
//		t5 = sin(pitch * 0.5);
//
//		//Set head tracking rotation
//		pose.qRotation.w = t0 * t2 * t4 + t1 * t3 * t5;
//		pose.qRotation.x = t0 * t3 * t4 - t1 * t2 * t5;
//		pose.qRotation.y = t0 * t2 * t5 + t1 * t3 * t4;
//		pose.qRotation.z = t1 * t2 * t4 - t0 * t3 * t5;
//
//		return pose;
//	}
//
//
//	void RunFrame()
//	{
//		// In a real driver, this should happen from some pose tracking thread.
//		// The RunFrame interval is unspecified and can be very irregular if some other
//		// driver blocks it for some periodic task.
//		if (m_unObjectId != vr::k_unTrackedDeviceIndexInvalid)
//		{
//			vr::VRServerDriverHost()->TrackedDevicePoseUpdated(m_unObjectId, GetPose(), sizeof(DriverPose_t));
//		}
//	}
//
//	std::string GetSerialNumber() const { return m_sSerialNumber; }
//
//private:
//	vr::TrackedDeviceIndex_t m_unObjectId;
//	vr::PropertyContainerHandle_t m_ulPropertyContainer;
//
//	std::string m_sSerialNumber;
//	std::string m_sModelNumber;
//
//	int32_t m_nWindowX;
//	int32_t m_nWindowY;
//	int32_t m_nWindowWidth;
//	int32_t m_nWindowHeight;
//	int32_t m_nRenderWidth;
//	int32_t m_nRenderHeight;
//	float m_flSecondsFromVsyncToPhotons;
//	float m_flDisplayFrequency;
//	float m_flIPD;
//};