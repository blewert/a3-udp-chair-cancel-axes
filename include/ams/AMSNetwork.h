#pragma once

#include <string>

namespace AMSA3
{
	namespace Network
	{
		const struct 
		{
			//IP is localhost by default
			std::string IP = "127.0.0.1";

			//Default port is 20777
			int PORT = 20777;

			//Default tick rate for the A3 is 40/s
			int TICK_SEND_RATE = 1000 / 40;
			int TICK_SAMPLE_RATE = 1000 / 5;

		} Settings;

		std::string GetPortString(void);
	}
}