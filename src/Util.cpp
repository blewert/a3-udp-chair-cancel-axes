#include "..\include\Util.h"

void AMSA3::Util::KillProcessByName(const char* filename) 
{
	//Create a snapshot
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);

	//Start enumerating
	BOOL hRes = Process32First(hSnapShot, &pEntry);

	while (hRes)
	{
		//While there are processes
		//..

		if(strcmpi(pEntry.szExeFile, filename) == 0)
		{
			//Does the file name match? If so, open it up
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);

			if (hProcess != NULL)
			{
				//Kill it hard
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}

		//Enumerate the next one (there may be more than one)
		hRes = Process32Next(hSnapShot, &pEntry);
	}

	//Close the snapshot
	CloseHandle(hSnapShot);
}


void AMSA3::Util::Log(const char* format, ...)
{
	//Make the list, start the list
	va_list vl;
	va_start(vl, format);

	//printf it out
	vprintf_s(format, vl);

	//End
	va_end(vl);
}