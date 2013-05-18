#pragma once


#include <vector>
#include <ctime>
#include <queue>
#include "IJMessage.h"
#include "Force.h"
#include "Collider.h"
#include "TransformComponent.h"
#include "KinematicComponent.h"
#include "Contact.h"
#include "RayCollider.h"
#include "PlaneCollider.h"
#include "Tile.h"
#include "InterSection.h"

typedef vector<PlaneCollider*>::iterator colliderIter;

typedef vector<Force*> forceVector;
typedef forceVector::iterator forceIter;

class PhysicsComponent: public TransformComponent
{
public:
	PhysicsComponent(void);
	~PhysicsComponent(void);

	void addCollider(PlaneCollider*);
	void setMainCollider( RayCollider * );
	void addForce(Force *f){forces.push_back(f);}
	void update(float dT);
	virtual Collider * getMainCollider(){
		return mainCollider;
	}
	void checkCollisionData(float dT);

	glm::mat4 getTransform(){return kinematics.getTransform();};
	KinematicComponent* getKinematics(){return &kinematics;}
protected:
	
	double game_time;
	double prev_game_time;
	double delta_t;
	double physics_lag_time;
	
	vector<PlaneCollider*> collisionData;
	PlaneCollider * closestPlane;

	KinematicComponent kinematics;
	RayCollider * mainCollider;
	forceVector forces;
};

