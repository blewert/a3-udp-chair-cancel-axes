#pragma once

#include <Windows.h>
#include <string>

namespace AMSA3
{
	namespace Network
	{
		class Packet
		{
		public:

#pragma pack(push, 1)
			struct UDPPacketData
			{
				bool useLocalVals;            // 4 byte bool value.  First byte = val, followed by 3 padding bytes. 
				float localAccel[3];          // 12 byte (3 x 4 byte) float vector.
				float localVel[3];            // 12 byte (3 x 4 byte) float vector.
				float globalVel[3];           // 12 byte (3 x 4 byte) float vector.
				float rotationMatrix[3][3];   // 36 byte (9 x 4 byte) float matrix.
				uint32_t packetTimeMillis;    // 4 byte integer value.
			};
#pragma pack(pop)
		};
	}
}