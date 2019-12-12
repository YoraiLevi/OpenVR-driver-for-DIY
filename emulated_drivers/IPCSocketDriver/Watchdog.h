#pragma once
#include <thread>
class CWatchdog : public vr::IVRWatchdogProvider
{
public:
	// Inherited via IVRWatchdogProvider
	virtual EVRInitError Init(IVRDriverContext* pDriverContext) override;
	virtual void Cleanup() override;
	//CWatchdog()
	//{
	//	m_pWatchdogThread = nullptr;
	//}

	//virtual vr::EVRInitError Init(vr::IVRDriverContext* pDriverContext);
	//virtual void Cleanup();

private:
	std::thread* m_pWatchdogThread;

};

