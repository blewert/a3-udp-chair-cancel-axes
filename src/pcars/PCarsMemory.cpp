#include "..\..\include\pcars\PCarsMemory.h"

using namespace PCars;

SharedMemoryClient::SharedMemoryClient(void)
{
}

SharedMemoryClient::~SharedMemoryClient(void)
{
}

void SharedMemoryClient::BlockUntilDetected(bool waitingAnimation)
{
	if (!waitingAnimation)
	{
		while ((this->game = this->GetSharedMemory()) == NULL);
	}
	else
	{
		const int delay = 100;
		while ((this->game = this->GetSharedMemory()) == NULL)
		{
			Sleep(delay);
			std::cout << "\b\\" << std::flush;
			Sleep(delay);
			std::cout << "\b|" << std::flush;
			Sleep(delay);
			std::cout << "\b/" << std::flush;
			Sleep(delay);
			std::cout << "\b-" << std::flush;
		}

		std::cout << std::endl;
	}
}

SharedMemoryData::SharedMemory* PCars::SharedMemoryClient::GetSharedMemory(void) const
{
	// Open the memory-mapped file
	HANDLE fileHandle = OpenFileMappingA(PAGE_READONLY, FALSE, MAP_OBJECT_NAME);

	if (fileHandle == NULL)
		return NULL;

	// Get the data structure
	SharedMemoryData::SharedMemory* sharedData = new SharedMemoryData::SharedMemory;

	//Get map
	sharedData = (SharedMemoryData::SharedMemory*)MapViewOfFile(fileHandle, PAGE_READONLY, 0, 0, sizeof(SharedMemoryData::SharedMemory));

	if (sharedData == NULL)
	{
		CloseHandle(fileHandle);
		return NULL;
	}

	// Ensure we're sync'd to the correct data version
	if (sharedData->mVersion != SharedMemoryData::SHARED_MEMORY_VERSION)
		return NULL;
	
	//And return it 
	return sharedData;
}
