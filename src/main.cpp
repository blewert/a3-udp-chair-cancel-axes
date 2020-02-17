#include "../include/main.h"


void main(void)
{
	//Create a new axis cancel program
	AxisCancelProgram* program = new AxisCancelProgram("none");

	//Delete it 
	delete program;
}