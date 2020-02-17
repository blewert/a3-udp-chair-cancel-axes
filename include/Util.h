#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <TlHelp32.h>

namespace AMSA3
{
	class Util
	{
	public:
		static void KillProcessByName(const char* filename);
		static void Log(const char* format, ...);
	};
}