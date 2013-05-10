#pragma once
#include "Collider.h"
#include "TransformComponent.h"
#include "KinematicComponent.h"
#include "Contact.h"
#include <map>

typedef void (*CollisionBehavior)(Contact*);

class PhysicsComponent: public TransformComponent
{
public:
	PhysicsComponent(void);
	~PhysicsComponent(void);

	void addCollider(Collider*, CollisionBehavior);
	void update(float dT){
		kinematics.update(dT);
	};
	glm::mat4 getTransform(){return kinematics.getTransform();};
protected:
	KinematicComponent kinematics;
	map<Collider*, CollisionBehavior> collisionData;
};

