#ifndef FULL_SCREEN_BLUR_H
#define FULL_SCREEN_BLUR_H


class Camera;
class Object;
class Texture;


class FullScreenBlur
{
public:

	FullScreenBlur(Camera* camera, float blurFactor = 0.67f);
	~FullScreenBlur();

	void SetBlurFactor(float blurFactor);
	float GetBlurFactor();
	float& BlurFactor();

	void SetRadialBlurFactor(float radialBlurFactor);
	float GetRadialBlurFactor();

	void Update();

private:

	float		_screenDistance;

	Camera*		_parentCamera;

	Image*		_screenImage;
	Texture*	_screenTexture;
	Object*		_screenQuad;

};


#endif // FULL_SCREEN_BLUR_H