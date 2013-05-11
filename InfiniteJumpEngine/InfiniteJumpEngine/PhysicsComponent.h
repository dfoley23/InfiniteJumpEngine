#pragma once
#include "Collider.h"
#include "TransformComponent.h"
#include "KinematicComponent.h"
#include "Contact.h"
#include <vector>

class PhysicsComponent: public TransformComponent
{
public:
	PhysicsComponent(void);
	~PhysicsComponent(void);

	void addCollider(Collider*);
	void setMainCollider( Collider * );
	void applyImpulse( glm::vec3 impulse );
	void update(float dT);
	glm::mat4 getTransform(){return kinematics.getTransform();};
protected:
	KinematicComponent kinematics;
	Collider * mainCollider;
	vector<Collider*> collisionData;
};

