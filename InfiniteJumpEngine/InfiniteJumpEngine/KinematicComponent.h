#pragma once
#include "PositionComponent.h"

class KinematicComponent : public PositionComponent
{
public:
	KinematicComponent(void);
	~KinematicComponent(void);
	glm::vec3 getPosition(){return position;};
	float getX(){return position.x;};
	float getY(){return position.x;};
	float getZ(){return position.x;};
	void setPosition(glm::vec3 vec){position = vec;};
	void setPosition(float x, float y, float z){setX(x);setY(y);setZ(z);}
	void setX(float v){position.x = v;};
	void setY(float v){position.y = v;};
	void setZ(float v){position.z = v;};
	glm::mat4 getTransform();
protected:
	glm::vec3 position;
};

