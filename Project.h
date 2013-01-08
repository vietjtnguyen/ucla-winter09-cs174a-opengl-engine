#ifndef PROJECT_H
#define PROJECT_H


// Forward declarations
class Camera;


void Initialize();
void MainLoop(float dt);
void CleanUp();
void AdditionalRendering();

#define SCENE01_ENDTIME 10.0f
void Scene01(float time, float dt);

#define SCENE02_ENDTIME 20.0f
void Scene02(float time, float dt);

#define SCENE03_ENDTIME 25.0f
void Scene03(float time, float dt);

#define SCENE04_ENDTIME 40.0f
void Scene04(float time, float dt);

#define SCENE05_ENDTIME 50.0f
void Scene05(float time, float dt);

#define SCENE06_ENDTIME 60.0f
void Scene06(float time, float dt);

#define SCENE07_ENDTIME 70.0f
void Scene07(float time, float dt);


#endif // PROJECT_H