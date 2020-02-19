#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string>

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

		private:
			std::string ip;
			int port;
			int tickRate = 0;
			unsigned long long ticks = 0;
			SOCKET sock = INVALID_SOCKET;

			void InitialiseWinsock(void);

			//bool update(void);
			//void sendData(SimphynityUDPPacket* packet);
			//void initWinsock(void);

			/*SOCKET sock;

			struct addrinfo* result = NULL,
				* ptr = NULL,
				hints;*/

			/*int ticks;
			int tick_rate;*/
		};
	}
}
//
//#include <string>
//#include "Simphynity.h"
//
