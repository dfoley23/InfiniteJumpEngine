
#ifndef CAMERA_H
#define CAMERA_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

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
