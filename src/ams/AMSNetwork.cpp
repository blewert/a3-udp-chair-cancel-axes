#include "..\..\include\ams\AMSNetwork.h"

std::string AMSA3::Network::GetPortString(void)
{
	return std::to_string(Network::Settings.PORT);
}

