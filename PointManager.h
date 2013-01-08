#ifndef POINT_MANAGER_H
#define POINT_MANAGER_H


#include <vector>

#include "Singleton.h"

using namespace std;


class Camera;
class Particle;


class PointManager
{
public:

	PointManager();

	~PointManager();

	Particle* EmitParticle();

	void Update(float dt);
	void Render(Camera* camera);

private:

	static unsigned int maxParticles;

	unsigned int		_liveParticles;
	vector<Particle*>	_particleList;

};
typedef Singleton<PointManager>	PointManagerSingleton;


#endif // POINT_MANAGER_H