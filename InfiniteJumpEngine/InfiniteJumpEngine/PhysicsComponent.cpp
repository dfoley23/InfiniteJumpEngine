#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(void)
{
	game_time = (double)clock()/CLOCKS_PER_SEC;
	delta_t = 0.17;
	physics_lag_time = 0.0;
	prev_game_time = game_time;
	kinematics.setParent( this );
	closestPlane = NULL;

}


PhysicsComponent::~PhysicsComponent(void)
{
}

/*
void PhysicsComponent::update( float dT ) {
	game_time = ((double)clock())/CLOCKS_PER_SEC;
	physics_lag_time += game_time - prev_game_time;
	if ( physics_lag_time > delta_t ) 
	{
		//check to see if the closest object has been hit yet
		pair<bool, double> intersect = mainCollider->predictIntersection(closestPlane);
		double intersectTime = 0.0f;
		//if it has send the collision then check for the next closest object
		if ( !intersect.first || intersect.second <= 0.0 ) {
			if ( closestPlane != NULL && intersect.first ) {
				sendMessage( this->getParent(), closestPlane, "InterSection", closestPlane->getNormal() );
			}
			for (colliderIter cIter = collisionData.begin();  cIter != collisionData.end(); ++cIter ) {
				intersect = mainCollider->predictIntersection((*cIter));
				if ( intersect.first && intersect.second < intersectTime && intersect.second > 0.0f ) {
					closestPlane = (*cIter);
					intersectTime = intersect.second;
				} else if ( !intersect.first && (*cIter) != closestPlane ) {
					//sendMessage( this->getParent(), (*cIter), "InterSection", (*cIter)->getNormal() );
				}
			}
		}
		glm::vec3 sumOfForces = glm::vec3(0,0,0);
		for (forceIter i = forces.begin(); i != forces.end(); i++){
			(*i)->update(dT);
			sumOfForces += (*i)->getValue();
		}
		kinematics.applyImpulse( sumOfForces );
		kinematics.update(dT);
		physics_lag_time -= delta_t;
	}
	prev_game_time = game_time;
}
*/

void PhysicsComponent::update( float dT ) {
	pair<bool, double> intersect;
	pair<bool, double> closestIntersect = pair<bool, double>(false,0.0f);
	PlaneCollider* closest = NULL;
	for (colliderIter cIter = collisionData.begin();  cIter != collisionData.end(); ++cIter ) {
		intersect = mainCollider->predictIntersection((*cIter));
		if ( intersect.first && intersect.second > 0.0 && intersect.second < dT ) {
			if ( !closestIntersect.first || intersect.first < closestIntersect.first ){
				closest = (*cIter);
				closestIntersect = intersect;
			}
		}
	}
	if ( closestIntersect.first && closestIntersect.second < dT ){
		sendMessage( getParent(), closest, "InterSection", closest->getNormal() );
	}
	glm::vec3 sumOfForces = glm::vec3(0,0,0);
	for (forceIter i = forces.begin(); i != forces.end(); i++){
		(*i)->update(dT);
		sumOfForces += (*i)->getValue();
	}
	kinematics.applyImpulse( sumOfForces );
	kinematics.update(dT);
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