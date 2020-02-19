#include "../include/main.h"



void main(void)
{
	//Create a new axis cancel program
	AxisCancelProgram* program = new AxisCancelProgram("none");

	Vector3 a(1, 0, 1);
	Vector3 b(0, 1, 0);
	a = (a - b) * 2;

	while (program->running)
		program->Update();
	
	printf("%f %f %f", a.data.x, a.data.y, a.data.z);


	//Delete it 
	delete program;
}