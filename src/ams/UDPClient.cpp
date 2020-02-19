#include "../include/ams/UDPClient.h"

using namespace AMSA3;
using namespace AMSA3::Network;

UDPClient::UDPClient(const std::string& ip, int port, int tickRate) : ip(ip), port(port), tickRate(tickRate)
{
	//initialise winsock
	this->InitialiseWinsock();
}

AMSA3::Network::UDPClient::~UDPClient(void)
{
	
}


bool UDPClient::NeedsUpdate(void)
{
	//Get current tick count
	unsigned long long currentTicks = GetTickCount64();

	//Return value is false initially
	bool returnValue = false;

	//Check difference
	if ((currentTicks - this->ticks) >= this->tickRate)
	{
		//Reset current ticks
		this->ticks = GetTickCount64();

		//Set return value to true
		returnValue = true;
	}

	//Return if there was a reset needed
	return returnValue;
}

void UDPClient::InitialiseWinsock(void)
{
	//Initialise winsock
	WSADATA wsaData;

	//Start up
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	//failed? don't continue
	if (result != 0)
		throw new std::exception("UDPClient - WSAStartup failed.");

	//Make some variables for the next bit
	struct addrinfo* addrResult = NULL, *ptr = NULL, hints;

	//Initialise hints with some zero memory
	ZeroMemory(&hints, sizeof(hints));

	//Set up for UDP traffic
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	//Get the address info
	result = getaddrinfo(this->ip.c_str(), &(*std::to_string(this->port).c_str()), &hints, &addrResult);

	//failed? don't continue
	if (result != 0)
		throw new std::exception("UDPClient - getaddrinfo failed.");

	// Attempt to connect to an address until one succeeds
	for (ptr = addrResult; ptr != NULL; ptr = ptr->ai_next)
	{
		try
		{
			//Create a SOCKET for connecting to server
			this->sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

			//Is this socket invalid? throw an error if so
			if (this->sock == INVALID_SOCKET)
				throw new std::exception("Failed to create socket.");

			//we have a socket, so lets try connect to the address
			result = connect(this->sock, ptr->ai_addr, (int)ptr->ai_addrlen);

			if (result == SOCKET_ERROR) 
			{
				//Socket error? close it and try again
				closesocket(this->sock);
				this->sock = INVALID_SOCKET;
				continue;
			}

			//Otherwise break -- we're good
			break;
		}
		catch(std::exception e)
		{
			WSACleanup();
		}
	}

	//Free address info up
	freeaddrinfo(addrResult);

	//Send some initial stuff
	send(this->sock, "ping", 4, 0);
}

void AMSA3::Network::UDPClient::sendData(const char* packet, unsigned int length) const
{
	send(this->sock, packet, length, 0);
}

void AMSA3::Network::UDPClient::sendData(Packet::UDPPacketData* packet) const
{
	send(this->sock, (char*)packet, sizeof(Packet::UDPPacketData), 0);
}

