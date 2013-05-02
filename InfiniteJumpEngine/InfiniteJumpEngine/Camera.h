
#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"
#include "glIncludes.h"

class Camera
{
public:
	
    Camera ( );
	
    virtual ~Camera ( );

	glm::mat4 cam, proj;
	glm::vec3 lightPos;
	virtual void update(float dT);

protected:

private:
    void initAttributes ( ) ;
};

#endif //CAMERA_H
