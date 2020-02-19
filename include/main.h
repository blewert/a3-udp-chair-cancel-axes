#pragma once

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>

//internal ams stuff & core headers
#include "ams/AMSNetwork.h"
#include "ams/AMSPacket.h"
#include "ams/UDPClient.h"
#include "Vector3.h"
#include "Util.h"

//stuff built on ams
#include "AxCancel.h"

//Usings
using namespace AMSA3;
using namespace AMSA3::Math;
using Vector3 = Math::Vector3;