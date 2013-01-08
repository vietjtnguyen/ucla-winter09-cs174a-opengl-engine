#ifndef WORLD_H
#define WORLD_H


#include <vector>

#include "FrameSaver.h"
#include "Singleton.h"
#include "Timer.h"
#include "Vectors.h"

#include <GL/gl.h>


// Namespaces
using namespace std;


typedef void (*WorldInitFunc)(void);
typedef void (*WorldMainLoopFunc)(float);
typedef void (*WorldCleanUpFunc)(void);
typedef void (*WorldRenderFunc)(void);
typedef void (*WorldWindowResizeFunc)(int, int);


class World
{
public:

// Default functions

	World();

	~World();

// Global render data functions

	void SetWindowSize(int width, int height);
	void SetWindowSize(Vector2i windowSize);
	Vector2i GetWindowSize();
	float GetAspectRatio();

	void SetAmbientColor(float r, float g, float b, float a);
	void SetAmbientColor(Vector4f color);
	Vector4f GetAmbientColor();

	enum FogMode
	{
		Linear = 0,
		Exponential = 1,
		Exponential2 = 2
	};
	void EnableFog();
	void DisableFog();
	void SetFogMode(FogMode fogMode);
	void SetFogDensity(float density);
	void SetFogColor(Vector4f rgb);
	void SetFogNear(float near);
	void SetFogFar(float far);

	void SetAnimating(bool state);
	void ToggleAnimating();
	bool IsAnimating();

	void SetRecording(bool state);
	void ToggleRecording();
	bool IsRecording();
	void SaveFrame();
	void Record();

// Global timing data functions

	void UpdateTimer();
	void UpdateTimer(float dt);

	void SetDtMultiplier(float mult);
	float GetDtMultiplier();

	void SetTime(float time);
	float GetTime();
	float GetDt();

// Engine functions

	static void RegisterInitializationFunction(WorldInitFunc func);
	static void RegisterMainLoopFunction(WorldMainLoopFunc func);
	static void RegisterCleanUpFunction(WorldCleanUpFunc func);
	static void RegisterRenderFunction(WorldRenderFunc func);
	static void RegisterWindowResizeFunction(WorldWindowResizeFunc func);
	static vector<WorldRenderFunc>* GetRenderFunctions();

	static void Initialize(int argc, char** argv);
	static void CleanUp();
	static void Update();

private:

// Global render data

	Vector2i	_windowSize;
	float		_aspectRatio;

	Vector4f	_ambientColor;

	bool		_animate;
	bool		_record;
	FrameSaver	_frameSaver;

// Global timing data

	Timer		_timer;

	float		_time;
	float		_dt;
	float		_dtMultiplier;

// Global engine data

	static vector<WorldInitFunc>			_initializationFunc;
	static vector<WorldMainLoopFunc>		_mainLoopFunc;
	static vector<WorldCleanUpFunc>			_cleanUpFunc;
	static vector<WorldRenderFunc>			_renderFunc;
	static vector<WorldWindowResizeFunc>	_windowResizeFunc;

};
typedef Singleton<World>	WorldSingleton;


#endif // WORLD_H