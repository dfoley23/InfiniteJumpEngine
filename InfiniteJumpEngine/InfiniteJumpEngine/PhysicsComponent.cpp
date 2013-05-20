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
	cFriction = -0.5f;
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
	glm::vec3 f = kinematics.vel.getPosition() * cFriction;
	//f.y = 0.0f;
	friction.setVector( f );
	glm::vec3 sumOfForces = glm::vec3(0,0,0);
	for (forceIter i = forces.begin(); i != forces.end(); i++){
		(*i)->update(dT);
		sumOfForces += (*i)->getValue();
	}
	kinematics.applyImpulse( sumOfForces );
	checkCollisionData( dT );
	kinematics.update(dT);
}

void PhysicsComponent::checkCollisionData(float dT) {
	pair<bool, double> intersect;
	pair<bool, double> closestIntersect = pair<bool, double>(false,0.0f);
	PlaneCollider* closest = NULL;
	PlaneCollider* lastClosest = NULL;
	bool hitUnSolidPlane = false;
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
			if ( intersect.first && abs(intersect.second) < dT ) {
				if ( !closestIntersect.first 
					|| abs(intersect.second) < abs(closestIntersect.second) )
				{
					if ( !hitUnSolidPlane || (*cIter)->isSolidPlane() ) 
					{
						closest = (*cIter);
						closestIntersect = intersect;
					}
				}
			}
		}
		if ( closest ){
			if ( !closest->isSolidPlane() ) { 
				hitUnSolidPlane = true;
			}
			//cout << closestIntersect.second << endl;
			kinematics.update(closestIntersect.second/2.0);
			sendMessage( getParent(), closest, "InterSection", glm::vec4( closest->getNormal(), 1.0) );
			sendMessage( closest, getParent(), "InterSection", glm::vec4( closest->getNormal(), 1.0) );
			dT -= closestIntersect.second/2.0;
		}
	}

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