#include "Camera.h"
#include "Image.h"
#include "Object.h"
#include "Texture.h"
#include "World.h"

#include "FullScreenBlur.h"


FullScreenBlur::FullScreenBlur(Camera* camera, float blurFactor)
:_screenDistance(0.0f)
,_parentCamera(camera)
,_screenImage(NULL)
,_screenTexture(NULL)
,_screenQuad(NULL)
{
	if( camera )
	{
		World* world = WorldSingleton::Get();
		Vector2f size = camera->GetViewportSize();

		this->_screenImage = new Image(
			(unsigned int)(size.width*world->GetWindowSize().width),
			(unsigned int)(size.height*world->GetWindowSize().height),
			RGB8 );

		this->_screenTexture = new Texture(this->_screenImage);

		this->_screenDistance = camera->GetNearDraw()+1.0f;

		this->_screenQuad = new Object();
		this->_screenQuad->StartRecording();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
		this->_screenQuad->StopRecording();
		this->_screenQuad->SetPosition(0.0f, 0.0f, -this->_screenDistance/Tan(this->_parentCamera->GetFieldOfView()/2.0f));
		this->_screenQuad->SetScale(this->_screenDistance, this->_screenDistance, 1.0f);
		this->_screenQuad->SetColor(Object::Diffuse, Vector4f(1.0f, 1.0f, 1.0f, blurFactor));
		this->_screenQuad->SetColor(Object::Emission, Vector4f(1.0f, 1.0f, 1.0f, 0.0f));
		this->_screenQuad->SetTexture(this->_screenTexture);
		this->_screenQuad->SetRenderOrder(Entity::Foreground);
		this->_screenQuad->Parent(camera);
	}
}


FullScreenBlur::~FullScreenBlur()
{
	delete this->_screenQuad;
	delete this->_screenTexture;
	delete this->_screenImage;
}


void FullScreenBlur::SetBlurFactor(float blurFactor)
{
	this->_screenQuad->Color(Object::Diffuse).a = blurFactor;
}


float FullScreenBlur::GetBlurFactor()
{
	return this->_screenQuad->Color(Object::Diffuse).a;
}


float& FullScreenBlur::BlurFactor()
{
	return this->_screenQuad->Color(Object::Diffuse).a;
}


void FullScreenBlur::SetRadialBlurFactor(float radialBlurFactor)
{
	this->_screenQuad->Scale().x = radialBlurFactor*2.0f;
	this->_screenQuad->Scale().y = this->_screenQuad->Scale().x;
}


float FullScreenBlur::GetRadialBlurFactor()
{
	return this->_screenQuad->Scale().x/2.0f;
}


void FullScreenBlur::Update()
{
	this->_screenQuad->SetPosition(0.0f, 0.0f, -this->_screenDistance/Tan(this->_parentCamera->GetFieldOfView()/2.0f));

	glReadBuffer(GL_BACK);
	unsigned int width = this->_screenImage->GetSize().width;
	unsigned int height = this->_screenImage->GetSize().height;
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)this->_screenImage->GetData());
	this->_screenTexture->ReloadTexture();
}