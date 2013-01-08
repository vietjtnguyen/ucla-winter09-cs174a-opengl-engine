#ifndef PARTICLE_H
#define PARTICLE_H


#include "Animators.h"
#include "Vectors.h"


class Camera;
class Texture;


class Particle
{
public:

	Particle();

	~Particle();

	enum Type
	{
		ScreenFacing,
		BillBoard,
		VectorAligned
	};

	enum BlendMode
	{
		Normal = 0,
		Additive = 1,
		Subtractive = 2
	};

	Particle::Type& GetType();
	Particle::BlendMode& GetBlendMode();
	float& Life();
	float& MaxLife();
	float& Rotation();
	Vector3f& Position();
	Vector3f& Velocity();
	Vector3f& Direction();
	Vector4f& Color();
	Animator2f*& Size();

	void SetTexture(Texture* texture);
	Texture* GetTexture();

	float& Depth();


	void Update(float dt);
	void Render(Camera* camera, unsigned int i, bool drawAxes = false);

private:

	Type		_type;
	BlendMode	_blendMode;

	float		_life;
	float		_maxLife;

	float		_rotation;
	Vector3f	_position;
	Vector3f	_velocity;
	Vector3f	_direction;
	Vector4f	_color;
	Animator2f*	_size;

	Texture*	_texture;

	float		_depth;

};


inline bool CompareParticles(Particle* left, Particle* right)
{
	return ( left->Depth() > right->Depth() );
}


#endif // PARTICLE_H