
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
	virtual void update(glm::vec3 pos);
	void switchProfile( int profile );
protected:

private:
	int cameraProfile;
    void initAttributes ( ) ;
};

#endif CAMERA_H
