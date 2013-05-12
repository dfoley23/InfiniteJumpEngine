#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(void)
{
	game_time = (double)clock()/CLOCKS_PER_SEC;
	delta_t = 0.17;
	physics_lag_time = 0.0;
	prev_game_time = game_time;
	kinematics.setParent( this );
}


PhysicsComponent::~PhysicsComponent(void)
{
}

void PhysicsComponent::update( float dT ) {
	game_time = ((double)clock())/CLOCKS_PER_SEC;
	physics_lag_time += game_time - prev_game_time;
	if ( physics_lag_time > delta_t ) 
	{
		for (colliderIter cIter = collisionData.begin(); cIter != collisionData.end(); ++cIter ) {
			if ( mainCollider->isColliding(*cIter) ){
				break;
			}
		}
		kinematics.update( delta_t );
		physics_lag_time -= delta_t;
	}
	prev_game_time = game_time;
}

void PhysicsComponent::applyImpulse( glm::vec3 impulse ){
	kinematics.applyImpulse( impulse );
}

void PhysicsComponent::setMainCollider( Collider * collider){ 
	mainCollider = collider;
}

void PhysicsComponent::addCollider(Collider* collider){ 
	this->collisionData.push_back( collider );
}

void tileCollision(Contact* contact){

}

void wallCollision(Contact* contact){

}

void cupCollision(Contact* contact){

}