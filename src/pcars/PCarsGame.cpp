#include "..\..\include\pcars\PCarsGame.h"

using namespace PCars::SharedMemoryData;
using namespace AMSA3::Math;

PCars::PCarsGame::PCarsGame(void)
{
	//Create the shared memory client
	memory = new SharedMemoryClient();
}

PCars::PCarsGame::~PCarsGame(void)
{
	delete memory;
}

void PCars::PCarsGame::BlockUntilMemoryDetected(void)
{
	//Just call memory->blockUntil...()
	this->memory->BlockUntilDetected(true);
}

Vector3 PCars::PCarsGame::GetLocalVelocity(void) const
{
	return Vector3(memory->game->mLocalVelocity[0], memory->game->mLocalVelocity[1], memory->game->mLocalVelocity[2]);
}

Vector3 PCars::PCarsGame::GetLocalAccel(void) const
{
	return Vector3(memory->game->mLocalAcceleration[0], memory->game->mLocalAcceleration[1], memory->game->mLocalAcceleration[2]);
}

Vector3 PCars::PCarsGame::GetWorldVelocity(void) const
{
	return Vector3(memory->game->mWorldVelocity[0], memory->game->mWorldVelocity[1], memory->game->mWorldVelocity[2]);
}

std::string PCars::PCarsGame::GetRaceStateString(void) const
{
	switch (memory->game->mRaceState)
	{
		case RACESTATE_DISQUALIFIED: return "DISQUALIFIED";
		case RACESTATE_DNF: return "DNF";
		case RACESTATE_FINISHED: return "FINISHED";
		case RACESTATE_INVALID: return "INVALID";
		case RACESTATE_MAX: return "MAX";
		case RACESTATE_NOT_STARTED: return "NOT STARTED";
		case RACESTATE_RACING: return "RACING";
		case RACESTATE_RETIRED: return "RETIRED";
		default:
			return "UNKNOWN";
	}
}

std::string PCars::PCarsGame::GetGameStateString(void) const
{
	switch (memory->game->mGameState)
	{
		case GAME_EXITED: return "EXITED";
		case GAME_FRONT_END: return "FRONT_END";
		case GAME_INGAME_PAUSED: return "PAUSED";
		case GAME_INGAME_PLAYING: return "PLAYING";
		case GAME_MAX: return "MAX";
		default:
			return "UNKNOWN";
	}
}

std::string PCars::PCarsGame::GetSessionStateString(void) const
{
	switch (memory->game->mSessionState)
	{
		case SESSION_INVALID: return "INVALID";
		case SESSION_FORMATION_LAP: return "FORMATION_LAP";
		case SESSION_MAX: return "MAX";
		case SESSION_PRACTICE: return "PRACTICE";
		case SESSION_QUALIFY: return "QUALIFY";
		case SESSION_RACE: return "RACE";
		case SESSION_TEST: return "TEST";
		case SESSION_TIME_ATTACK: return "TIME_ATTACK";
		default:
			return "UNKNOWN";
	}
}

std::string PCars::PCarsGame::GetCarName(void) const
{
	return std::string(memory->game->mCarName);
}

std::string PCars::PCarsGame::GetTrackName(void) const
{
	return std::string(memory->game->mTrackLocation);
}

float PCars::PCarsGame::GetTrackLength(void) const
{
	return memory->game->mTrackLength;
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
