#include "../include/main.h"



void main(void)
{
	//Create a new axis cancel program
	AxisCancelProgram* program = new AxisCancelProgram("none");

	//Log out that we're gonna block until project cars 2 is found.
	Util::Log("Created program. Blocking until Project CARS 2 is found.  ");

	//Now, block until PCars2 is detected
	program->projectCars->BlockUntilMemoryDetected();

	//Log out that we've found project cars 2
	Util::Log("Project CARS 2 found!\n");

	while (program->running)
		program->Update();	

	//Delete it 
	delete program;
}