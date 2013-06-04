
#ifndef CAMERA_H
#define CAMERA_H

#include "glIncludes.h"

class Camera
{
public:
	
    Camera ( );
	
    virtual ~Camera ( );

	glm::mat4 cam, proj;
	glm::vec3 lightPos;
	void update(glm::vec3, glm::vec3);
	void switchProfile( int profile );
	void changeLightPos( float x, float y, float z );
	void changeEyePos( float x, float y, float z );
	void changeLookAtPos( float x, float y, float z );
	//void changeLightPos( glm::vec3 pos );
	//void changeEyePos( glm::vec3 pos );
	//void changeLookAtPos( glm::vec3 pos );

	glm::vec3 camEye;
	glm::vec3 camLookAt;
	glm::vec3 camUp;
	glm::vec3 getDir( );
	glm::vec3 camDir;
protected:

private:
	int cameraProfile;
    void initAttributes ( ) ;
};

#endif CAMERA_H
