#pragma once

#include <windows.h>
#include "Util.h"

namespace AMSA3
{
	class AxisCancelProgram
	{
	private:
		//vars
		const char* TELEMETRY_WRITER_EXE_NAME = "project-cars-telemetry-writer.exe";

		//funcs
		BOOL WINAPI ConsoleControlCallback(DWORD ctrlType);
	};
}