#include <algorithm>

#include "Camera.h"
#include "Particle.h"

#include "PointManager.h"


using namespace std;


unsigned int PointManager::maxParticles = 1200;
PointManager* PointManagerSingleton::_instance = NULL;


PointManager::PointManager()
:_liveParticles(0)
,_particleList()
{
	for( unsigned int i = 0; i < PointManager::maxParticles; ++i )
	{
		Particle* particle = new Particle();
		if( particle )
		{
			this->_particleList.push_back(particle);
		}
		else
		{
			break;
		}
	}
}


PointManager::~PointManager()
{
}


Particle* PointManager::EmitParticle()
{
	if( this->_liveParticles < this->_particleList.size() )
	{
		Particle* particle = this->_particleList.at(this->_liveParticles);
		this->_liveParticles++;
		return particle;
	}
	return NULL;
}


void PointManager::Update(float dt)
{
	for( unsigned int i = 0; i < this->_liveParticles; ++i )
	{
		Particle* particle = this->_particleList.at(i);
		if( particle )
		{
			particle->Update(dt);
			if( particle->Life() <= 0.0f )
			{
				Core::Swap<Particle*>(this->_particleList.at(i), this->_particleList.at(this->_liveParticles-1));
			}
		}
	}

	// Depth sort particles
	if( this->_liveParticles > 0 )
	{
		sort(this->_particleList.begin(), this->_particleList.begin()+(this->_liveParticles-1), CompareParticles);
	}
}


void PointManager::Render(Camera* camera)
{
	for( unsigned int i = 0; i < this->_liveParticles; ++i )
	{
		Particle* particle = this->_particleList.at(i);
		if( particle )
		{
			particle->Render(camera, i);
		}
	}
}