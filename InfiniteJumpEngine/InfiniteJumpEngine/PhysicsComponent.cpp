#include "PhysicsComponent.h"


const int PhysicsComponent::COLLISION_CHECKS = 5;

PhysicsComponent::PhysicsComponent(void)
{
	game_time = (double)clock()/CLOCKS_PER_SEC;
	delta_t = 0.17;
	physics_lag_time = 0.0;
	prev_game_time = game_time;
	kinematics.setParent( this );
	closestPlane = NULL;
	cFriction = -1.0f;
	friction.start();
	forces.push_back(&friction);
}


PhysicsComponent::~PhysicsComponent(void)
{
	vector<PlaneCollider*>().swap(collisionData);
	delete &kinematics;
	delete mainCollider;
}

void PhysicsComponent::update( float dT ) {
	pair<bool, double> intersect;
	pair<bool, double> closestIntersect = pair<bool, double>(false,0.0f);
	PlaneCollider* closest = NULL;
	PlaneCollider* lastClosest = NULL;
	glm::vec3 f = kinematics.vel.getPosition() * cFriction;
	f.y = 0.0f;
	friction.setVector( f );
	glm::vec3 sumOfForces = glm::vec3(0,0,0);
	for (forceIter i = forces.begin(); i != forces.end(); i++){
		(*i)->update(dT);
		sumOfForces += (*i)->getValue();
	}
	kinematics.applyImpulse( sumOfForces );
	for (int check = 0; 
		check < COLLISION_CHECKS 
		&& (check == 0 
			|| (closest != lastClosest)); 
		check++)
		{
		lastClosest = closest;
		closest = NULL;
		closestIntersect.first = false;
		mainCollider->setRayStart( kinematics.loc.getPosition() );
		mainCollider->setDirection( kinematics.vel.getPosition() );
		for (colliderIter cIter = collisionData.begin();  cIter != collisionData.end(); ++cIter ) {
			intersect = mainCollider->predictIntersection((*cIter));
			//if ( intersect.first && intersect.second > 0.0 && intersect.second < dT ) {
			if ( intersect.first && abs(intersect.second) < dT ) {
				if ( !closestIntersect.first 
					|| abs(intersect.second) < abs(closestIntersect.second) 
					//|| (intersect.first == closestIntersect.first 
					//	&& (mainCollider->getRayStart() - closest->getPointOnPlane()).length() 
					//		< (mainCollider->getRayStart() -(*cIter)->getPointOnPlane()).length() ) 
					)
				{
					closest = (*cIter);
					closestIntersect = intersect;
				}
			}
		}
		if ( closest ){
			//cout << closestIntersect.second << endl;
			kinematics.update(closestIntersect.second/2.0);
			sendMessage( getParent(), closest, "InterSection", closest->getNormal() );
			dT -= closestIntersect.second/2.0;
		}
	}
	kinematics.update(dT);
}

bool operator<(const InterSection &x1, const InterSection &x2 ){
	return (x1.getInterSectTime() < x2.getInterSectTime());
}

void PhysicsComponent::setMainCollider( RayCollider * collider){ 
	mainCollider = collider;
}

void PhysicsComponent::addCollider(PlaneCollider* collider){ 
	this->collisionData.push_back( collider );
}

void tileCollision(Contact* contact){

}

void wallCollision(Contact* contact){

}

void cupCollision(Contact* contact){

}