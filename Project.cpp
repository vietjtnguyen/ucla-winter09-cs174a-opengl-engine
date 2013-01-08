#include <iostream>

#include "Animators.h"
#include "BitmapImage.h"
#include "Camera.h"
#include "FullScreenBlur.h"
#include "Image.h"
#include "Light.h"
#include "Matrices.h"
#include "Mesh.h"
#include "Particle.h"
#include "PointManager.h"
#include "Object.h"
#include "Renderer.h"
#include "Terrain.h"
#include "Texture.h"
#include "World.h"

#include "Tank.h"

#include "Project.h"

#include <stdlib.h>


using namespace std;


#define HIGH_QUALITY


// Globals
Animatorf* timeline;

Camera* mainCamera;

FullScreenBlur* blurEffect;

Terrain* terrain;
Object* skyDome;
Light* sun;

Tank* redTank1;
Tank* redTank2;

Tank* blueTank1;
Tank* blueTank2;

Image* smokeStrip;
Texture* smokeTexture;


// Initialize
void Initialize()
{
	cout << "Initializing..." << endl;

	// Get world
	World* world = WorldSingleton::Get();

	world->SetWindowSize(500, 500);


	// Create animation timeline
	cout << endl << "Creating timeline(s)..." << endl;

	timeline = new Animatorf(); 
	timeline->SetPlayState(Forever);


	// Create camera(s)
	cout << endl << "Creating camera(s)..." << endl;
	
	mainCamera = new Camera(
		true,
		Vector2f(0, 0), Vector2f(1.0f, 1.0f),
		90.0f, 1.0f, 2048.0f);
	mainCamera->SetClearColor(0.2f, 0.4f, 0.9f, 1.0f);


	// Full screen quad for temporal effects
	cout << endl << "Setting up full screen effect..." << endl;
	blurEffect = new FullScreenBlur(mainCamera, 0.5f);


	// Create terrain
	cout << endl << "Creating terrain..." << endl;

#ifdef HIGH_QUALITY
	BitmapImage heightMap("media/terrainHeight.bmp");
	terrain = new Terrain((Image*)&heightMap);
	terrain->SetOffset(-256, -256);
	terrain->SetScale(16.0f, 384.0f, 16.0f); // w, d in [-4096, 4096], h in [0, 384]
#else
	BitmapImage heightMap("media/terrainHeightSmall.bmp");
	terrain = new Terrain((Image*)&heightMap);
	terrain->SetOffset(-64, -64);
	terrain->SetScale(64.0f, 384.0f, 64.0f);
#endif
	terrain->SetTexture(new Texture(new BitmapImage("media/terrainColor.bmp")));
	terrain->Update();


	// Create sky dome
	cout << endl << "Creating sky dome..." << endl;

	skyDome = new Object();
	skyDome->CreateSphere(256.0f, 32, 32);
	skyDome->SetRenderOrder(Entity::Background);
	skyDome->SetRenderSide(Object::BackFace);
#ifdef HIGH_QUALITY
	skyDome->SetTexture(new Texture(new BitmapImage("media/skyTexture.bmp")));
#else
	skyDome->SetTexture(new Texture(new BitmapImage("media/skyTextureSmall.bmp")));
#endif
	skyDome->SetColor(Object::Diffuse, Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	skyDome->SetColor(Object::Emission, Vector4f(1.0f, 1.0f, 1.0f, 0.0f));
	skyDome->SetPosition(0.0f, -32.0f, 0.0f);
	skyDome->Parent(mainCamera);
	skyDome->SetInheritRotation(false);


	// Create light(s)
	cout << endl << "Creating light(s)..." << endl;

	world->SetAmbientColor(0.65f, 0.65f, 0.8f, 1.0f);

	sun = new Light();
	sun->MakeDirectional();
	sun->SetDirection(Vector3f::Direction(40.0f, 180.0f+37.3f));
	sun->SetShininess(5000.0f);
	sun->SetSpotExponent(2.0f);


	// Load tanks
	cout << endl << "Loading tanks..." << endl;

	redTank1 = new Tank();
	redTank1->SetPosition(0.0f, 96.0f, 2048.0f);
	redTank1->ResetCornerHeights();

	redTank2 = new Tank();
	redTank2->SetPosition(-64.0f, 96.0f, 2048.0f+96.0f);
	redTank2->ResetCornerHeights();

	blueTank1 = new Tank();
	blueTank1->SetPosition(-436.0f, 384.0f, -64.0f);
	blueTank1->ResetCornerHeights();
	blueTank1->SetEulerRotation(0.0f, -230.0f, 0.0f);

	blueTank2 = new Tank();
	blueTank2->SetPosition(692.0f, 384.0f, -48.0f);
	blueTank2->ResetCornerHeights();
	blueTank2->SetEulerRotation(0.0f, 160.0f, 0.0f);


	// Load particle textures
	cout << endl << "Loading particle textures..." << endl;

	smokeStrip = new BitmapImage("media/heavySmoke.bmp");
	smokeTexture = new Texture(smokeStrip);
}


// Main loop
void MainLoop(float dt)
{
	// Get world
	World* world = WorldSingleton::Get();

	// Update animation value
	timeline->Update(dt);

	// Display scenes
	if( timeline->GetTime() <= SCENE01_ENDTIME )
	{
		Scene01(timeline->GetTime(), dt);
	}
	else if( timeline->GetTime() <= SCENE02_ENDTIME )
	{
		Scene02(timeline->GetTime(), dt);
	}
	else if( timeline->GetTime() <= SCENE03_ENDTIME )
	{
		Scene03(timeline->GetTime(), dt);
	}
	else if( timeline->GetTime() <= SCENE04_ENDTIME )
	{
		Scene04(timeline->GetTime(), dt);
	}
	else if( timeline->GetTime() <= SCENE05_ENDTIME )
	{
		Scene05(timeline->GetTime(), dt);
	}
	else if( timeline->GetTime() <= SCENE06_ENDTIME )
	{
		Scene06(timeline->GetTime(), dt);
	}
	else if( timeline->GetTime() <= SCENE07_ENDTIME )
	{
		Scene07(timeline->GetTime(), dt);
	}

	// Update particles
	PointManager* pointManager = PointManagerSingleton::Get();
	pointManager->Update(dt);

	// Update full screen blur
	blurEffect->Update();
}


// Clean up
void CleanUp()
{
	cout << "Cleaning up..." << endl;

	// Get world
	World* world = WorldSingleton::Get();
}


// Additional rendering
void AdditionalRendering()
{
	// Get world
	World* world = WorldSingleton::Get();

	// Draw global origin
	//DrawAxes(32.0f);

	// Draw ground grid
	//DrawGrid(
	//	Vector3f(0.0f, 0.0f, 0.0f),
	//	Vector3f(1.0f, 0.0f, 0.0f),
	//	Vector3f(0.0f, 0.0f, -1.0f),
	//	-40.0f, 40.0f, 40.0f,
	//	-20.0f, 20.0f, 20.0f,
	//	Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
}


// Scene 01
void Scene01(float time, float dt)
{
	static const float orbitSpeed = 36.0f;

	// Get world
	World* world = WorldSingleton::Get();


	// Move tanks
	redTank1->SetTargetPosition(Vector3f(160.0f, 0.0f, -16.0f));
	redTank2->SetTargetPosition(Vector3f(60.0f, 0.0f, -16.0f));
	
	redTank1->SetTargetVelocity(60.0f);
	redTank2->SetTargetVelocity(60.0f);

	redTank1->Update(dt, terrain);
	redTank2->Update(dt, terrain);

	redTank1->OrientToTerrain(terrain, dt);
	redTank2->OrientToTerrain(terrain, dt);
	blueTank1->OrientToTerrain(terrain, dt);
	blueTank2->OrientToTerrain(terrain, dt);

	redTank1->OrientTurret(10.0f, 45.0f+Sin(time*60.0f)*30.0f);
	redTank2->OrientTurret(15.0f, -30.0f+Sin(time*80.0f)*45.0f);


	// Spit particles
	static Trigger* particleSpawnTimer = new Trigger(0.25f);
	static Lerp2f* sizeLerp = new Lerp2f(Vector2f(4.0f, 4.0f), Vector2f(8.0f, 8.0f));

	particleSpawnTimer->SetPlayState(Loop);
	particleSpawnTimer->Update(dt);

	if( particleSpawnTimer->DoTrigger() )
	{
		cout << "Trigger..." << endl;
		PointManager* pointManager = PointManagerSingleton::Get();
		Particle* particle;

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank1->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank2->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}
	}


	// Orbit camera
	mainCamera->SetFieldOfView(90.0f);
	mainCamera->SetEulerRotation(
		-3.0f,
		mainCamera->GetEulerRotation().y+dt*orbitSpeed,
		0.0f);

	float yaw = mainCamera->GetEulerRotation().y;

	mainCamera->SetPosition(
		redTank1->GetPosition().x+Sin(yaw)*64.0f,
		redTank1->GetPosition().y+12.0f,
		redTank1->GetPosition().z+Cos(yaw)*64.0f);


	// Update blur effect
	blurEffect->SetBlurFactor(0.6f);
}


// Scene 02
void Scene02(float time, float dt)
{
	static const float cameraBobbleSpeed = 0.5f;
	static const float cameraBobble = 0.1f;
	static float wobbleParameter = 0.0f;

	// Get world
	World* world = WorldSingleton::Get();


	// Move tanks
	redTank1->SetTargetPosition(Vector3f(160.0f, 0.0f, -16.0f));
	redTank2->SetTargetPosition(Vector3f(60.0f, 0.0f, -16.0f));
	
	redTank1->SetTargetVelocity(60.0f);
	redTank2->SetTargetVelocity(60.0f);

	redTank1->Update(dt, terrain);
	redTank2->Update(dt, terrain);

	redTank1->OrientToTerrain(terrain, dt);
	redTank2->OrientToTerrain(terrain, dt);
	blueTank1->OrientToTerrain(terrain, dt);
	blueTank2->OrientToTerrain(terrain, dt);

	redTank1->OrientTurret(10.0f, 45.0f+Sin(time*60.0f)*30.0f);
	redTank2->OrientTurret(15.0f, -30.0f+Sin(time*80.0f)*45.0f);


	// Spit particles
	static Trigger* particleSpawnTimer = new Trigger(0.25f);
	static Lerp2f* sizeLerp = new Lerp2f(Vector2f(4.0f, 4.0f), Vector2f(8.0f, 8.0f));

	particleSpawnTimer->SetPlayState(Loop);
	particleSpawnTimer->Update(dt);

	if( particleSpawnTimer->DoTrigger() )
	{
		cout << "Trigger..." << endl;
		PointManager* pointManager = PointManagerSingleton::Get();
		Particle* particle;

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank1->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank2->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}
	}


	// Aim camera wobbly
	wobbleParameter += 30.0f*(1.0f+sin(wobbleParameter*0.4f)*0.05f)*dt;

	mainCamera->SetFieldOfView(Approach(mainCamera->GetFieldOfView(), 20.0f, 0.5f, dt));
	mainCamera->SetPosition(-20.0f, 300.0f, 0.0f);
	mainCamera->SetEulerRotation(
		-10.0f+sin(wobbleParameter*0.2f*cameraBobbleSpeed)*3.0f*cameraBobble-5,
		185.0f+sin(wobbleParameter*0.1f*cameraBobbleSpeed)*6.0f*cameraBobble,
		sin(wobbleParameter*0.05f*cameraBobbleSpeed)*30.0f*cameraBobble);


	// Update blur effect
	blurEffect->SetBlurFactor(0.8f);
}


// Scene 03
void Scene03(float time, float dt)
{
	// Get world
	World* world = WorldSingleton::Get();


	// Move tanks
	redTank1->SetTargetPosition(Vector3f(160.0f, 0.0f, -16.0f));
	redTank2->SetTargetPosition(Vector3f(60.0f, 0.0f, -16.0f));
	
	redTank1->SetTargetVelocity(30.0f);
	redTank2->SetTargetVelocity(30.0f);

	redTank1->Update(dt, terrain);
	redTank2->Update(dt, terrain);

	redTank1->OrientToTerrain(terrain, dt);
	redTank2->OrientToTerrain(terrain, dt);
	blueTank1->OrientToTerrain(terrain, dt);
	blueTank2->OrientToTerrain(terrain, dt);

	redTank1->OrientTurret(10.0f, 45.0f+Sin(time*60.0f)*30.0f);
	redTank2->OrientTurret(15.0f, -30.0f+Sin(time*80.0f)*45.0f);


	// Spit particles
	static Trigger* particleSpawnTimer = new Trigger(0.25f);
	static Lerp2f* sizeLerp = new Lerp2f(Vector2f(4.0f, 4.0f), Vector2f(8.0f, 8.0f));

	particleSpawnTimer->SetPlayState(Loop);
	particleSpawnTimer->Update(dt);

	if( particleSpawnTimer->DoTrigger() )
	{
		cout << "Trigger..." << endl;
		PointManager* pointManager = PointManagerSingleton::Get();
		Particle* particle;

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank1->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank2->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}
	}


	// Orbit camera
	mainCamera->SetFieldOfView(90.0f);

	mainCamera->SetEulerRotation(-6.0f, 100.0f, 0.0f);

	float yaw = mainCamera->GetEulerRotation().y;

	mainCamera->SetPosition(
		redTank1->GetPosition().x+Sin(yaw)*64.0f,
		redTank1->GetPosition().y+18.0f,
		redTank1->GetPosition().z+24.0f+Cos(yaw)*64.0f);


	// Update blur effect
	blurEffect->SetBlurFactor(0.7);
}


// Scene 04
void Scene04(float time, float dt)
{
	static const float cameraBobbleSpeed = 0.5f;
	static const float cameraBobble = 0.1f;
	static float wobbleParameter = 0.0f;

	// Get world
	World* world = WorldSingleton::Get();


	// Move tanks
	redTank1->SetTargetPosition(Vector3f(160.0f, 0.0f, -16.0f));
	redTank2->SetTargetPosition(Vector3f(60.0f, 0.0f, -16.0f));
	blueTank1->SetTargetPosition(Vector3f(-128.0f, 0.0f, -64.0f));
	blueTank2->SetTargetPosition(Vector3f(432.0f, 0.0f, -80.0f));
	
	redTank1->SetTargetVelocity(30.0f);
	redTank2->SetTargetVelocity(30.0f);
	blueTank1->SetTargetVelocity(30.0f);
	blueTank2->SetTargetVelocity(30.0f);

	redTank1->Update(dt, terrain);
	redTank2->Update(dt, terrain);
	blueTank1->Update(dt, terrain);
	blueTank2->Update(dt, terrain);

	redTank1->OrientToTerrain(terrain, dt);
	redTank2->OrientToTerrain(terrain, dt);
	blueTank1->OrientToTerrain(terrain, dt);
	blueTank2->OrientToTerrain(terrain, dt);

	blueTank1->OrientTurret(-5.0f, Approach(blueTank1->GetTurretOrientation().y, -80.0f, 1.0f, dt));
	blueTank2->OrientTurret(-10.0f, Approach(blueTank2->GetTurretOrientation().y, 90.0f, 1.0f, dt));


	// Spit particles
	static Trigger* particleSpawnTimer = new Trigger(0.25f);
	static Lerp2f* sizeLerp = new Lerp2f(Vector2f(4.0f, 4.0f), Vector2f(8.0f, 8.0f));

	particleSpawnTimer->SetPlayState(Loop);
	particleSpawnTimer->Update(dt);

	if( particleSpawnTimer->DoTrigger() )
	{
		cout << "Trigger..." << endl;
		PointManager* pointManager = PointManagerSingleton::Get();
		Particle* particle;

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank1->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}

		particle = pointManager->EmitParticle();
		if( particle )
		{
			particle->MaxLife() = Rnd(0.25f, 1.5f);
			particle->Life() = particle->MaxLife();
			particle->Rotation() = Rnd(0.0f, 360.0f);
			particle->Position() = redTank2->GetPosition()+Vector3f(Rnd(-4.0f, 4.0f), Rnd(0.0f, 4.0f), Rnd(-4.0f, 4.0f));
			particle->Velocity().Set(Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f), Rnd(-1.5f, 1.5f));
			particle->Size() = sizeLerp;
			particle->SetTexture(smokeTexture);
			particle->Color().Set(140.0f/255.0f, 128.0f/255.0f, 112.0f/255.0f, 0.75f);
		}
	}


	// Orbit camera
	wobbleParameter += 30.0f*(1.0f+sin(wobbleParameter*0.4f)*0.05f)*dt;

	mainCamera->SetFieldOfView(90.0f);
	mainCamera->SetPosition(500.0f, 700.0f, -300.0f);
	mainCamera->SetEulerRotation(
		-60.0f+sin(wobbleParameter*0.2f*cameraBobbleSpeed)*3.0f*cameraBobble-5,
		120.0f+sin(wobbleParameter*0.1f*cameraBobbleSpeed)*6.0f*cameraBobble,
		sin(wobbleParameter*0.05f*cameraBobbleSpeed)*30.0f*cameraBobble);


	// Update blur effect
	blurEffect->SetBlurFactor(0.6f);
}


// Scene 05
void Scene05(float time, float dt)
{
	// Get world
	World* world = WorldSingleton::Get();
}


// Scene 06
void Scene06(float time, float dt)
{
	// Get world
	World* world = WorldSingleton::Get();
}


// Scene 07
void Scene07(float time, float dt)
{
	// Get world
	World* world = WorldSingleton::Get();
}