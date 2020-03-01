#include "../include/main.h"



int main(int argc, char* argv[])
{
	//Create a new axis cancel program
	AxisCancelProgram* program = new AxisCancelProgram("none");

	//Log out that we're gonna block until project cars 2 is found.
	Util::Log("Created program. Blocking until Project CARS 2 is found.  ");

	//Now, block until PCars2 is detected
	//program->projectCars->BlockUntilMemoryDetected();
	program->SetTestMode();

	//Log out that we've found project cars 2
	Util::Log("Project CARS 2 found!\n");

	//Create the visualiser
	GUI::Visualiser* visualiser = new GUI::Visualiser(program->projectCars);

	//Set up visualiser
	program->visualiser = visualiser;

	while (program->running)
	{
		//Update program state
		program->Update();

		//Update visualiser & render
		visualiser->Update();
		visualiser->Render();
	}

	//Delete it 
	delete program;
	delete visualiser;

	return 0;
}