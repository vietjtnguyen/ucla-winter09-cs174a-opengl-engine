#ifndef CAMERA_H
#define CAMERA_H


#include "Entity.h"
#include "Generic.h"
#include "GlobalList.h"
#include "Vectors.h"
#include "World.h"

#include <GL/glut.h>


class Camera : public Entity, public GlobalList<Camera>
{
public:

	Camera(
		bool windowRelative,
		Vector2f viewportPosition, Vector2f viewportSize,
		float fov, float nearDraw, float farDraw,
		GLenum drawBuffer = GL_BACK, bool active = true);

	virtual ~Camera();

	void SetViewportWindowRelative(bool state);
	bool IsViewportWindowRelative();

	void SetViewportPosition(float x, float y);
	void SetViewportPosition(Vector2f position);
	Vector2f GetViewportPosition();

	void SetViewportSize(float width, float height);
	void SetViewportSize(Vector2f size);
	Vector2f GetViewportSize();
	float GetAspectRatio();

	void SetFieldOfView(float degrees);
	float GetFieldOfView();

	void SetNearDraw(float nearDraw);
	float GetNearDraw();

	void SetFarDraw(float farDraw);
	float GetFarDraw();

	void SetClearColor(float r, float g, float b, float a);
	void SetClearColor(Vector4f color);
	Vector4f GetClearColor();

	void SetDrawBuffer(GLenum drawBuffer);
	GLenum GetDrawBuffer();

	void UpdateViewport();
	void Draw();

	virtual void Render();

private:

	bool		_windowRelative;

	Vector2f	_viewportPosition;
	Vector2f	_viewportSize;
	Vector2i	_actualViewportPosition;
	Vector2i	_actualViewportSize;
	float		_aspectRatio;

	float		_fieldOfView;

	float		_nearDraw;
	float		_farDraw;

	Vector4f	_clearColor;

	// TODO (Viet Nguyen): Expand this in the future to support multiple buffers. Remember to query the maximum number of buffers that can be drawn to using glGet(SetActiveState). Use that as a maximum size to a vector of buffer pointers. UPDATE (01/19/2009): This actually might not work because the multiple buffers command (glDrawBuffers) doesn't seem to specify GL_BACK and GL_FRONT.
	GLenum		_drawBuffer;
};
typedef Camera::GlobalList<Camera> GlobalCameraList;


#endif // CAMERA_H