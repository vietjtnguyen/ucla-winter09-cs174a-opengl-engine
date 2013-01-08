#include "Camera.h"
#include "Trash.h"
#include "InputCallbacks.h"
#include "Light.h"
#include "Object.h"
#include "Renderer.h"
#include "Types.h"

#include "World.h"

#include "GL/glut.h"


// Static definitions
World* WorldSingleton::_instance = NULL;

vector<WorldInitFunc> World::_initializationFunc;
vector<WorldMainLoopFunc> World::_mainLoopFunc;
vector<WorldCleanUpFunc> World::_cleanUpFunc;
vector<WorldRenderFunc> World::_renderFunc;
vector<WorldWindowResizeFunc> World::_windowResizeFunc;


// Default constructor
World::World()
:_windowSize(640, 480)
,_aspectRatio()
,_ambientColor()
,_animate(false)
,_record(false)
,_frameSaver()
,_timer()
,_time(0.0f)
,_dt(0.0f)
,_dtMultiplier(1.0f)
{
	this->_aspectRatio =
		(float)this->_windowSize.width/(float)this->_windowSize.height;

	this->SetAmbientColor(0.2f, 0.2f, 0.2f, 1.0f);
}


// Destructor
World::~World()
{
}


// -----------------------------------------------------------------------------
// Render data functions


// Set display size
void World::SetWindowSize(int width, int height)
{
	this->_windowSize.Set(width, height);
	this->_aspectRatio =
		(float)this->_windowSize.width/(float)this->_windowSize.height;
	glutReshapeWindow(this->_windowSize.width, this->_windowSize.height);

	// Call window resize functions
	for( unsigned int i = 0; i < World::_windowResizeFunc.size(); ++i )
	{
		WorldWindowResizeFunc func = World::_windowResizeFunc.at(i);
		(*func)(width, height);
	}
}

void World::SetWindowSize(Vector2i windowSize)
{
	this->SetWindowSize(windowSize.width, windowSize.height);
}


// Get display size
Vector2i World::GetWindowSize()
{
	return this->_windowSize;
}


// Get aspect ratio
float World::GetAspectRatio()
{
	return this->_aspectRatio;
}


// Set ambient light color
void World::SetAmbientColor(float r, float g, float b, float a)
{
	this->_ambientColor.Set(r, g, b, a);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (float*)this->_ambientColor);

}

void World::SetAmbientColor(Vector4f color)
{
	this->SetAmbientColor(color.r, color.g, color.b, color.a);
}


// Get ambient light color
Vector4f World::GetAmbientColor()
{
	return this->_ambientColor;
}


// Set animating state
void World::SetAnimating(bool state)
{
	this->_animate = state;
}


// Toggle animating state
void World::ToggleAnimating()
{
	this->_animate ^= true;
}


// Get animating state
bool World::IsAnimating()
{
	return this->_animate;
}


// Set recording state
void World::SetRecording(bool state)
{
	this->_record = state;
	if( this->_record )
	{
		this->_frameSaver.ResetFrameCount();
	}
	else
	{
		this->_frameSaver.ConvertToMpeg();
	}
}


// Toggle animating state
void World::ToggleRecording()
{
	this->_record ^= true;
	if( this->_record )
	{
		this->_frameSaver.ResetFrameCount();
	}
	else
	{
		this->_frameSaver.ConvertToMpeg();
	}
}


// Get animating state
bool World::IsRecording()
{
	return this->_record;
}


// Save frame
void World::SaveFrame()
{
	this->_frameSaver.SaveFrame("screenshot.ppm", this->_windowSize.width, this->_windowSize.height);
}


// Record
void World::Record()
{
	this->_frameSaver.Record(this->_windowSize.width, this->_windowSize.height);
}


// -----------------------------------------------------------------------------
// Timing data functions


// Update timer
void World::UpdateTimer()
{
	if( this->_record )
	{
		this->_dt = 0.03333f;
	}
	else
	{
		this->_dt = this->_timer.GetElapsedTime();
	}
	this->_time += this->_dt*this->_dtMultiplier;

	this->_timer.Reset();
}

void World::UpdateTimer(float dt)
{
	if( this->_record )
	{
		this->_dt = 0.03333f;
	}
	else
	{
		this->_dt = dt;
	}
	this->_time += this->_dt*this->_dtMultiplier;

	this->_timer.Reset();
}


// Set dt multiplier
void World::SetDtMultiplier(float mult)
{
	this->_dtMultiplier = mult;
}


// Get dt multiplier
float World::GetDtMultiplier()
{
	return this->_dtMultiplier;
}


// Set time
void World::SetTime(float time)
{
	this->_time = time;
}


// Get time
float World::GetTime()
{
	return this->_time;
}


// Get delta time
float World::GetDt()
{
	return this->_dt*this->_dtMultiplier;
}


// -----------------------------------------------------------------------------
// Engine functions


// World initialization
void World::Initialize(int argc, char** argv)
{
	// Get world
	World* world = WorldSingleton::Get();

	// Initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Create window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(world->GetWindowSize()[0], world->GetWindowSize()[1]);
	glutCreateWindow(argv[0]);
    
	// Set up render settings
    //glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);

	// Set up blending
	glEnable(GL_BLEND);

	// Set up anti-aliasing
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	
	// Set up depth settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	// Set up normals
    //glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

	// Set up texturing
	glEnable(GL_TEXTURE_2D);

	// Set up lights
    glEnable(GL_LIGHTING);
	float zeroValue = 0.0f;
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, &zeroValue);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); // NOTE (Viet Nguyen): This isn't supported in this environment's OpenGL.

	// Set up pixel storage methods
	// Do not pad pixel data rows to a certain byte multiple
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Set input callbacks
	glutKeyboardFunc(KeyboardUpdateCallback);
	glutSpecialFunc(KeyboardSpecialUpdateCallback);
	glutMouseFunc(MouseButtonUpdateCallback);
	glutMotionFunc(MouseMoveUpdateCallback);

	// Set main callback
	glutIdleFunc(World::Update);

	// Set display callbacks
	glutDisplayFunc(DisplayUpdateCallback);
	glutReshapeFunc(WindowReshapeCallback);

	// Call initialization functions
	for( unsigned int i = 0; i < World::_initializationFunc.size(); ++i )
	{
		WorldInitFunc func = World::_initializationFunc.at(i);
		(*func)();
	}
}


// World clean up
void World::CleanUp()
{
	// Call clean up functions
	for( unsigned int i = 0; i < World::_cleanUpFunc.size(); ++i )
	{
		WorldInitFunc func = World::_cleanUpFunc.at(i);
		(*func)();
	}

	Trash::CleanUp();

	// Delete world
	delete WorldSingleton::Get();
}


// World update
void World::Update()
{
	// Get world data
	World* world = WorldSingleton::Get();

	// Update timers
	if( world->IsAnimating() == 1 )
	{
		if( world->IsRecording() == 0 )
		{
			// Update at a smooth rate regardless of refresh rate
			world->UpdateTimer();
		}
		else
		{
			// Record at a constant 30 frames per second
			world->UpdateTimer(0.033333f);
		}
	}
	else
	{
		// Pause all movement
		world->UpdateTimer(0.0f);
	}

	// Simulation update
	float dt = world->GetDt();

	// Call main loop functions
	for( unsigned int i = 0; i < World::_mainLoopFunc.size(); ++i )
	{
		WorldMainLoopFunc func = World::_mainLoopFunc.at(i);
		(*func)(dt);
	}

	glutPostRedisplay();
}


// Register initialization function
void World::RegisterInitializationFunction(WorldInitFunc func)
{
	World::_initializationFunc.push_back(func);
}


// Register initialization function
void World::RegisterMainLoopFunction(WorldMainLoopFunc func)
{
	World::_mainLoopFunc.push_back(func);
}


// Register clean up function
void World::RegisterCleanUpFunction(WorldCleanUpFunc func)
{
	World::_cleanUpFunc.push_back(func);
}


// Register render function
void World::RegisterRenderFunction(WorldRenderFunc func)
{
	World::_renderFunc.push_back(func);
}


// Register window resize function
void World::RegisterWindowResizeFunction(WorldWindowResizeFunc func)
{
	World::_windowResizeFunc.push_back(func);
}


// Get render functions
vector<WorldInitFunc>* World::GetRenderFunctions()
{
	return &World::_renderFunc;
}