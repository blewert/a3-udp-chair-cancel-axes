#include "..\include\AxCancel.h"

using namespace AMSA3;
const char* AMSA3::AxisCancelProgram::TELEMETRY_WRITER_EXE_NAME = "project-cars-telemetry-writer.exe";


//
// constructors
//

AMSA3::AxisCancelProgram::AxisCancelProgram(AxisCancelMode operatingMode) : operatingMode(operatingMode)
{
	//First, set console control callback
	SetConsoleCtrlHandler(ConsoleControlCallback, TRUE);
}

//Just call other constructor
AMSA3::AxisCancelProgram::AxisCancelProgram(const std::string& operatingMode) : AxisCancelProgram(this->GetModeFromName(operatingMode)) {}

//Empty destructor
AMSA3::AxisCancelProgram::~AxisCancelProgram(void) { }




//
// functions
//

AxisCancelMode AMSA3::AxisCancelProgram::GetModeFromName(const std::string& name) const
{
	//Just a simple switch (but im too lazy to write a switch
	if      (name == "none")   return AxisCancelMode::CANCEL_NONE;
	else if (name == "all")    return AxisCancelMode::CANCEL_ALL;
	else if (name == "surge")  return AxisCancelMode::CANCEL_SURGE;
	else if (name == "roll")   return AxisCancelMode::CANCEL_ROLL;

	//Otherwise throw an error -- something funky is happening
	else throw new std::exception("Unrecognised operating mode specified.");
}


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
