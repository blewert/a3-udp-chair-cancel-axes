#pragma once

#include "ams/AMSNetwork.h"
#include "ams/AMSPacket.h"
#include "ams/UDPClient.h"
#include "pcars/PCarsGame.h"
#include "gui/AMSgui.h"
#include "Util.h"
#include "Vector3.h"

#include <windows.h>
#include <string>

using namespace AMSA3::Math;
using namespace AMSA3::Network;

namespace AMSA3
{
	//The axis cancel mode -- surge (+y), roll (+x), none (+x+y), all (-x-y)
	enum class AxisCancelMode
	{
		CANCEL_SURGE,
		CANCEL_ROLL,
		CANCEL_NONE,
		CANCEL_ALL
	};

	class AxisCancelProgram
	{
	public:

		//The current operating mode/condition for this program
		AxisCancelMode operatingMode;
		bool running = true;
		Packet::UDPPacketData* packet;
		PCars::PCarsGame* projectCars;

		//Public methods
		AxisCancelMode GetModeFromName(const std::string& name) const;
		void SetupUDPClient(void);
		void Update(void);
		void SetTestMode(void);
		void SendTestData(void);
		void SendPacket(Vector3& accel, Vector3& localVel, Vector3& worldVel) const;

		//Constructors & destructors
		AxisCancelProgram(AxisCancelMode operatingMode);
		AxisCancelProgram(const std::string& operatingMode);
		~AxisCancelProgram(void);

		GUI::Visualiser* visualiser = NULL;

	private:
		//vars
		Network::UDPClient* udpClient;

		bool testMode = false;
		static const char* TELEMETRY_WRITER_EXE_NAME;
		static constexpr float MPH_TO_MS = 0.44704f;
		static constexpr float MS_TO_G   = 0.101972f;

		Vector3 axisScale = Vector3(1.0f, 1.0f, 1.0f);
		static constexpr float MAX_CAR_SPEED_MPH = 200.0f;
	

		//funcs
		static BOOL WINAPI ConsoleControlCallback(DWORD ctrlType);
	};
}