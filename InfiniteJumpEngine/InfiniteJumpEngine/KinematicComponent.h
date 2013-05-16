#pragma once
#ifndef KINEMATIC_COMPONENT_H
#define KINEMATIC_COMPONENT_H
#include "IJMessage.h"
#include "PositionComponent.h"

class KinematicComponent : public TransformComponent
{
public:
	KinematicComponent(void);
	~KinematicComponent(void);
	glm::mat4 getTransform();
	void update(float dT);
	void applyImpulse( glm::vec3 impulse );
	void receiveMessage( IJMessage *m);

	PositionComponent loc;
	PositionComponent vel;
	PositionComponent acc;
};
#endif KINEMATIC_COMPONENT_H
