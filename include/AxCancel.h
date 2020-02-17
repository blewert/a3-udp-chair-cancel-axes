#pragma once

#include <windows.h>
#include "Util.h"
#include <string>

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

		//Public methods
		AxisCancelMode GetModeFromName(const std::string& name) const;

		//Constructors & destructors
		AxisCancelProgram(AxisCancelMode operatingMode);
		AxisCancelProgram(const std::string& operatingMode);
		~AxisCancelProgram(void);

	private:
		//vars
		static const char* TELEMETRY_WRITER_EXE_NAME;

		//funcs
		static BOOL WINAPI ConsoleControlCallback(DWORD ctrlType);
	};
}