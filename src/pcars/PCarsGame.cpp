#include "..\..\include\pcars\PCarsGame.h"

using namespace PCars::SharedMemoryData;
using namespace AMSA3::Math;

PCars::PCarsGame::PCarsGame(void)
{
	//Create the shared memory client
	memory = new SharedMemoryClient();

	//Block until the game is detected
	memory->BlockUntilDetected();
}

PCars::PCarsGame::~PCarsGame(void)
{
	delete memory;
}

inline Vector3 PCars::PCarsGame::GetLocalVelocity(void) const 
{
	return Vector3(memory->game->mLocalVelocity[0], memory->game->mLocalVelocity[1], memory->game->mLocalVelocity[2]);
}

inline Vector3 PCars::PCarsGame::GetLocalAccel(void) const
{
	return Vector3(memory->game->mLocalAcceleration[0], memory->game->mLocalAcceleration[1], memory->game->mLocalAcceleration[2]);
}

inline Vector3 PCars::PCarsGame::GetWorldVelocity(void) const
{
	return Vector3(memory->game->mWorldVelocity[0], memory->game->mWorldVelocity[1], memory->game->mWorldVelocity[2]);
}

bool PCars::PCarsGame::IsPlayerInGame(void) const
{
	return (memory->game->mGameState == GAME_INGAME_PAUSED || memory->game->mGameState == GAME_INGAME_PLAYING);
}

bool PCars::PCarsGame::IsPlayerInRaceSession(void) const
{
	return IsPlayerInGame() && (memory->game->mSessionState == SESSION_RACE);
}

bool PCars::PCarsGame::IsPlayerRacing(void) const
{
	return IsPlayerInRaceSession() && (memory->game->mRaceState == RACESTATE_RACING);
}

bool PCars::PCarsGame::IsRaceFinished(void) const
{
	return IsPlayerInRaceSession() && (memory->game->mRaceState == RACESTATE_FINISHED);
}

bool PCars::PCarsGame::IsWaitingForRaceStart(void) const
{
	return (memory->game->mRaceState == RACESTATE_INVALID || memory->game->mRaceState == RACESTATE_NOT_STARTED);
}
