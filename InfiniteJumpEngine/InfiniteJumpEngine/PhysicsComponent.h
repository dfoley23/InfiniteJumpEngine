#pragma once

#include "IJMessage.h"
#include "Force.h"
#include "Collider.h"
#include "TransformComponent.h"
#include "KinematicComponent.h"
#include "Contact.h"
#include <vector>

typedef vector<Force*> forceVector;
typedef forceVector::iterator forceIter;

class PhysicsComponent: public TransformComponent
{
public:
	PhysicsComponent(void);
	~PhysicsComponent(void);

	void addCollider(Collider*);
	void setMainCollider( Collider * );
	void applyImpulse( glm::vec3 impulse );
	void addForce(Force *f){forces.push_back(f);}
	void update(float dT);
	glm::mat4 getTransform(){return kinematics.getTransform();};
	KinematicComponent* getKinematics(){return &kinematics;}
protected:
	KinematicComponent kinematics;
	Collider * mainCollider;
	vector<Collider*> collisionData;
	forceVector forces;
};

