#ifndef RENDERER_H
#define RENDERER_H


#include "Vectors.h"


void DisplayUpdateCallback();
void WindowReshapeCallback(int width, int height);


void DrawAxes(float scale = 1.0f, float lineWidth = 1.0f);
void DrawGrid(
	Vector3f origin,
	Vector3f aAxis,
	Vector3f bAxis,
	float alo, float ahi, int asteps,
	float blo, float bhi, int bsteps,
	Vector4f color,
	bool overlay = false,
	float lineWidth = 1.0f);


#endif // RENDERER_H