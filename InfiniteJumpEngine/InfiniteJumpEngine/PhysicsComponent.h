#pragma once


#include <vector>
#include <ctime>
#include "IJMessage.h"
#include "Force.h"
#include "Collider.h"
#include "TransformComponent.h"
#include "KinematicComponent.h"
#include "Contact.h"
#include "PointCollider.h"

typedef vector<Collider*>::iterator colliderIter;

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
	virtual Collider * getMainCollider(){
		return mainCollider;
	}
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
	forceVector forces;
};

