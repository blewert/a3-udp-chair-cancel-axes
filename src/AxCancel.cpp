#include "..\include\AxCancel.h"

using namespace AMSA3;

BOOL WINAPI AMSA3::AxisCancelProgram::ConsoleControlCallback(DWORD ctrlType)
{
	if (ctrlType == CTRL_CLOSE_EVENT)
	{
		//Log out the event
		Util::Log("Closing telemetry writer ('%s')...\n", TELEMETRY_WRITER_EXE_NAME);
	
		//Kill the process and sleep for a second
		Util::KillProcessByName(TELEMETRY_WRITER_EXE_NAME);
		Sleep(1000);
	}

	//Return true
	return true;
}
