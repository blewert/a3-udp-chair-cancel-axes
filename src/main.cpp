#include "../include/main.h"


void main(void)
{
	Util::KillProcessByName("notepad.exe");
	Util::Log("hello %d %s %f", 50, "there", 3.1415f);
}