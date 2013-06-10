
#ifndef CAMERA_H
#define CAMERA_H

#include "glIncludes.h"
#include "luaIncludes.h"
#include "LuaBaseComponent.h"

using namespace std;
class Camera
{
public:
	
    Camera ( );

    virtual ~Camera ( );

	glm::mat4 cam, proj;
	glm::vec3 lightPos;
	void update();
	void setUsingScript( string scriptFile, LuaBaseComponent * luaBase );
	void changeLightPos( float x, float y, float z );
	void changeEyePos( float x, float y, float z );
	void changeLookAtPos( float x, float y, float z );
	void changeUpDir( float x, float y, float z);
	glm::vec3 getEyePos();
	glm::vec3 getLookAtPos();
private:
	glm::vec3 camEye;
	glm::vec3 camLookAt;
	glm::vec3 camUp;
	glm::vec3 camDir;
	bool usingScript;
	string updateScript;
	LuaBaseComponent * lua;
    void initAttributes ( ) ;
};

#endif CAMERA_H
