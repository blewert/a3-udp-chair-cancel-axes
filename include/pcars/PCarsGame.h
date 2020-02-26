#pragma once
#include <windows.h>
#include "PCarsMemory.h"
#include "Vector3.h"

namespace PCars
{
	using namespace AMSA3::Math;

	class PCarsGame
	{
	public:
		PCarsGame(void);
		~PCarsGame(void);

		SharedMemoryClient* memory;

		void BlockUntilMemoryDetected(void);

		Vector3 GetLocalVelocity(void) const;
		Vector3 GetLocalAccel(void) const;
		Vector3 GetWorldVelocity(void) const;

		bool IsPlayerInGame(void) const;
		bool IsPlayerInRaceSession(void) const;
		bool IsPlayerRacing(void) const;
		bool IsRaceFinished(void) const;
		bool IsWaitingForRaceStart(void) const;
	};
}