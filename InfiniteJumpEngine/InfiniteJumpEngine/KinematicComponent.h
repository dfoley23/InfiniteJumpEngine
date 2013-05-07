#pragma once
#include "PositionComponent.h"

class KinematicComponent : public TransformComponent
{
public:
	KinematicComponent(void);
	~KinematicComponent(void);
	glm::mat4 getTransform();
	void update(float dT);
protected:
	PositionComponent loc;
	PositionComponent vel;
	PositionComponent acc;
};

