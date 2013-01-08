// Computer Science 174A
// Section 1A
// Project 1
//
// Viet Nguyen
// 503-505-066

// Import standard libraries
#include <cmath>
#include <cstdlib>
#include <iostream>

// Import OpenGL related includes
#include <GL/glut.h>

// Import world
#include "World.h"

// Import project
#include "Project.h"


// Program entry point
int main(int argc, char** argv) 
{
	World::RegisterInitializationFunction(&Initialize);
	World::RegisterMainLoopFunction(&MainLoop);
	World::RegisterCleanUpFunction(&CleanUp);
	World::RegisterRenderFunction(&AdditionalRendering);

	World::Initialize(argc, argv);

	glutMainLoop();

	return 0;
}