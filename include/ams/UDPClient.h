#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string>
#include "AMSPacket.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "ws2_32")

#define DEFAULT_BUFLEN 512


namespace AMSA3
{
	namespace Network
	{
		class UDPClient
		{
		public:
			UDPClient(const std::string& ip, int port, int tickRate);
			~UDPClient(void);

			bool NeedsUpdate(void);

			void sendData(const char* packet, unsigned int length) const;
			void sendData(Packet::UDPPacketData* packet) const;

		private:
			std::string ip;
			int port;
			int tickRate = 0;
			unsigned long long ticks = 0;
			SOCKET sock = INVALID_SOCKET;

			void InitialiseWinsock(void);

		};
	}
}
