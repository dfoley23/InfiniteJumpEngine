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
	game_time = ((double)clock())/CLOCKS_PER_SEC;
	physics_lag_time += game_time - prev_game_time;
	if ( physics_lag_time > delta_t ) 
	{

		pair<bool, double> intersect;
		double intersectTime = 100000.0f;
		for (int i=0; i<static_cast<int>(collisionData.size()); i++ ) {
			intersect = mainCollider->predictIntersection(collisionData.at(i));
			if ( closestPlane == NULL || ( intersect.first && intersect.second < intersectTime) ) {
				//Tile * tile = (Tile*)(*cIter)->getParent();
				//cout << " closest Plane is: " << tile->getTileId();
				if ( intersect.second > 0.0f ) {
					closestPlane = collisionData.at(i);
					intersectTime = intersect.second;
				} else {
					sendMessage( this->getParent(), closestPlane, "InterSection", closestPlane->getNormal() );
				}
			} else if ( !intersect.first && collisionData.at(i) != closestPlane ) {
				//sendMessage( this->getParent(), (*cIter), "InterSection", (*cIter)->getNormal() );
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