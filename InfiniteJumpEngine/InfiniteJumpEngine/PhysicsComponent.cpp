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

void PhysicsComponent::update( float dT ) {
	pair<bool, double> intersect;
	pair<bool, double> closestIntersect = pair<bool, double>(false,0.0f);
	PlaneCollider* closest = NULL;
	/*for ( int i=0; i<static_cast<int>(meshCollision.size()); i++ ) {
		if ( pointCollider->isColliding( meshCollision.at( i ) ) ) {
			break;
		}
	}*/
	for (colliderIter cIter = collisionData.begin();  cIter != collisionData.end(); ++cIter ) {
		intersect = mainCollider->predictIntersection((*cIter));
		if ( intersect.first && intersect.second > 0.0 && intersect.second < dT ) {
			if ( !closestIntersect.first 
				|| intersect.second < closestIntersect.second 
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