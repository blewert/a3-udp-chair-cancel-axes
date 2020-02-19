#include "..\include\AxCancel.h"

using namespace AMSA3;
const char* AMSA3::AxisCancelProgram::TELEMETRY_WRITER_EXE_NAME = "project-cars-telemetry-writer.exe";



AMSA3::AxisCancelProgram::AxisCancelProgram(AxisCancelMode operatingMode) : operatingMode(operatingMode)
{
	//First, set console control callback
	SetConsoleCtrlHandler(ConsoleControlCallback, TRUE);

	//Then, make the UDP client
	this->SetupUDPClient();
}

//Just call other constructor
AMSA3::AxisCancelProgram::AxisCancelProgram(const std::string& operatingMode) : AxisCancelProgram(this->GetModeFromName(operatingMode)) {}

//Destructor
AMSA3::AxisCancelProgram::~AxisCancelProgram(void) 
{
	//Clean up
	delete udpClient;
}

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

void AMSA3::AxisCancelProgram::SetupUDPClient(void)
{
	//Get the IP, port and tick rate
	auto ip = Network::Settings.IP;
	auto port = Network::Settings.PORT;
	auto tickRate = Network::Settings.TICK_SEND_RATE;

	//Set up the UDP client
	this->udpClient = new Network::UDPClient(ip, port, tickRate);
}

void AMSA3::AxisCancelProgram::Update(void)
{
	if (this->udpClient->NeedsUpdate())
	{
		const char* data = "hello there mr";
		this->udpClient->sendData(data, strlen(data));

		printf("update");
	}
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
