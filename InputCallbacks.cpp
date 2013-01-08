#include <iostream>

#include "GL/glut.h"

#include "Matrices.h"
#include "Object.h"
#include "World.h"

#include "InputCallbacks.h"


using namespace std;


// Keyboard input update function
void KeyboardUpdateCallback(unsigned char key, int x, int y)
{
	// Get world
	World* world = WorldSingleton::Get();

	// Update key modifiers
	int modifiers = glutGetModifiers();

	int altDown = modifiers & GLUT_ACTIVE_ALT;
	int ctrlDown = modifiers & GLUT_ACTIVE_CTRL;
	int shiftDown = modifiers & GLUT_ACTIVE_SHIFT;

	// Act on key
	switch( key )
	{
		case 'q':
		case 27:
			World::CleanUp();
			exit(0);
		case 'a':
			world->ToggleAnimating();
			cout << altDown << ctrlDown << shiftDown << endl;
			break;
		case 'A':
			world->ToggleAnimating();
			cout << altDown << ctrlDown << shiftDown << endl;
			break;
		case 'r':
			world->ToggleRecording();
			break;
		case 's':
			world->SaveFrame();
			break;
		default:
			cout << altDown << ctrlDown << shiftDown << " " << (int)key << endl;
	}

	glutPostRedisplay();
}


// Keyboard special input update function
#include "FullScreenBlur.h"
extern FullScreenBlur* blurEffect;
void KeyboardSpecialUpdateCallback(int key, int x, int y)
{
	// Get world
	World* world = WorldSingleton::Get();

	// Act on key
	Matrix33f rotation;
	rotation.SetIdentity();
	switch( key )
	{
	case GLUT_KEY_UP:
		blurEffect->SetRadialBlurFactor(blurEffect->GetRadialBlurFactor()-0.05f);
		break;
	case GLUT_KEY_DOWN:
		blurEffect->SetRadialBlurFactor(blurEffect->GetRadialBlurFactor()+0.05f);
		break;
	}

	glutPostRedisplay();
}


// Mouse button input update function
void MouseButtonUpdateCallback(int button, int state, int x, int y)
{
	glutPostRedisplay();
}


// Mouse movement update function
void MouseMoveUpdateCallback(int x, int y)
{
	glutPostRedisplay();
}