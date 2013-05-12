#pragma once


#include <vector>
#include <ctime>
#include "IJMessage.h"
#include "Collider.h"
#include "TransformComponent.h"
#include "KinematicComponent.h"
#include "Contact.h"

typedef vector<Collider*>::iterator colliderIter;

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
	KinematicComponent* getKinematics(){return &kinematics;}
protected:
	
	double game_time;
	double prev_game_time;
	double delta_t;
	double physics_lag_time;

	KinematicComponent kinematics;
	Collider * mainCollider;
	vector<Collider*> collisionData;
};

