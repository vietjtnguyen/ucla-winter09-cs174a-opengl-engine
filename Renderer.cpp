#include "Camera.h"
#include "MathWrapper.h"
#include "World.h"

#include "Renderer.h"

#include <GL/glut.h>


// Primary display function
void DisplayUpdateCallback(void)
{
	// Get world
	World* world = WorldSingleton::Get();
	
	// Update cameras
	for( unsigned int i = 0; i < GlobalCameraList::GetListSize(); ++i )
	{
		Camera* camera = GlobalCameraList::GetListItem(i);
		camera->Draw();
	}

	// Double buffer
	glutSwapBuffers();

	// Set up frame recording
	if( world->IsRecording() == 1 )
	{
		world->Record();
	}
}


// Window reshape redraw and reinitialization function
void WindowReshapeCallback(int width, int height)
{
	// Get world
	World* world = WorldSingleton::Get();

	// Update world
	world->SetWindowSize(width, height);

	// Update camera viewports
	for( unsigned int i = 0; i < GlobalCameraList::GetListSize(); ++i )
	{
		Camera* camera = GlobalCameraList::GetListItem(i);
		camera->UpdateViewport();
	}
}


// Draw axes
void DrawAxes(float scale, float lineWidth)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//GLfloat oldLineWidth;
	//glGetFloatv(GL_LINE_WIDTH, &oldLineWidth);
	//glLineWidth(lineWidth);

	//GLboolean lineSmooth;
	//glGetBooleanv(GL_LINE_SMOOTH, &lineSmooth);
	//if( lineSmooth == GL_FALSE )
	//{
	//	glEnable(GL_LINE_SMOOTH);
	//}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glBegin(GL_LINES);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(scale, 0.0f, 0.0f);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, scale, 0.0f);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, scale);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//if( lineSmooth == GL_FALSE )
	//{
	//	glDisable(GL_LINE_SMOOTH);
	//}

	//glLineWidth(oldLineWidth);
}


// Draw grid
void DrawGrid(
	Vector3f origin,
	Vector3f aAxis,
	Vector3f bAxis,
	float alo, float ahi, int asteps,
	float blo, float bhi, int bsteps,
	Vector4f color,
	bool overlay,
	float lineWidth)
{
	glPolygonMode(GL_FRONT, GL_LINE);
	
	GLfloat oldLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &oldLineWidth);
	glLineWidth(lineWidth);

	//GLboolean lineSmooth;
	//glGetBooleanv(GL_LINE_SMOOTH, &lineSmooth);
	//if( lineSmooth == GL_FALSE )
	//{
	//	glEnable(GL_LINE_SMOOTH);
	//}

	if( overlay )
	{
		glDisable(GL_DEPTH_TEST);
	}

	//glDisable(GL_LIGHTING);
	
	float astep = (ahi-alo)/(float)asteps;
	float bstep = (bhi-blo)/(float)bsteps;

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINES);

		Vector3f lo;
		Vector3f hi;

		lo = origin+bAxis*blo;
		hi = origin+bAxis*bhi;
		for( float i = alo; i <= ahi; i += astep )
		{
			glVertex3fv((float*)(lo+aAxis*i));
			glVertex3fv((float*)(hi+aAxis*i));
		}

		lo = origin+aAxis*alo;
		hi = origin+aAxis*ahi;
		for( float i = blo; i <= bhi; i += bstep )
		{
			glVertex3fv((float*)(lo+bAxis*i));
			glVertex3fv((float*)(hi+bAxis*i));
		}
	glEnd();

	if( overlay )
	{
		glEnable(GL_DEPTH_TEST);
	}

	//glEnable(GL_LIGHTING);

	//if( lineSmooth == GL_FALSE )
	//{
	//	glDisable(GL_LINE_SMOOTH);
	//}

	glLineWidth(oldLineWidth);
}