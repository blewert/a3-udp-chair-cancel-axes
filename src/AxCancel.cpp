#include "..\include\AxCancel.h"

using namespace AMSA3;
const char* AMSA3::AxisCancelProgram::TELEMETRY_WRITER_EXE_NAME = "project-cars-telemetry-writer.exe";


AMSA3::AxisCancelProgram::AxisCancelProgram(AxisCancelMode operatingMode) : operatingMode(operatingMode)
{
	//First, set console control callback
	SetConsoleCtrlHandler(ConsoleControlCallback, TRUE);

	//Set up the local packet so it doesn't blow up later
	this->packet = new Packet::UDPPacketData();

	//Then, make the UDP client
	this->SetupUDPClient();

	//Now, create the game (block until it is found)
	projectCars = new PCars::PCarsGame();
}

//Just call other constructor
AMSA3::AxisCancelProgram::AxisCancelProgram(const std::string& operatingMode) : AxisCancelProgram(this->GetModeFromName(operatingMode)) {}

//Destructor
AMSA3::AxisCancelProgram::~AxisCancelProgram(void) 
{
	//Clean up
	delete udpClient;
	delete projectCars;
	delete packet;
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
		//Project cars is null now? Then the game has been closed...
		if (projectCars == NULL)
			return;

		//Player is not ingame? Then skip!
		if (!projectCars->IsPlayerInGame())
			return;

		//Get vector of each
		Vector3 accel = projectCars->GetLocalAccel();
		Vector3 lvel  = projectCars->GetLocalVelocity();
		Vector3 wvel  = projectCars->GetWorldVelocity();

		//Build the packet, send it
		this->SendPacket(accel, lvel, wvel);
	}
}

void AMSA3::AxisCancelProgram::SendPacket(Vector3& accel, Vector3& localVel, Vector3& worldVel) const
{
	//Scale each by multiplier (e.g. -1 for negation, 0 for cancel, etc.)
	accel     *= this->axisScale;
	localVel  *= this->axisScale;
	worldVel  *= this->axisScale;

	//Add on ms_to_g for accel
	accel += Vector3(0, MS_TO_G, 0);

	//Swizzle: sX -> sZ, sY -> sX, sZ -> sY
	accel.Swizzle('z', 'x', 'y');
	localVel.Swizzle('z', 'x', 'y');
	worldVel.Swizzle('z', 'x', 'y');

	//Local/world velocity needs to be normalised (200mph is the max)
	localVel /= (MPH_TO_MS * 200.0f);
	worldVel /= (MPH_TO_MS * 200.0f);

	//Set the packet to use local values because whatever
	packet->useLocalVals = true;

	//Copy all components
	memcpy(packet->localVel,   &localVel.data, sizeof(float) * 3);
	memcpy(packet->globalVel,  &worldVel.data, sizeof(float) * 3);
	memcpy(packet->localAccel, &accel.data,    sizeof(float) * 3);

	//Log acceleration
	Util::Log("accel = (%.2f, %.2f, %.2f)\n", accel.data.x, accel.data.y, accel.data.z);

	if (this->visualiser != NULL)
		this->visualiser->OnPacketSent(packet);

	//Return a copy of the packet
	udpClient->sendData(packet);
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
