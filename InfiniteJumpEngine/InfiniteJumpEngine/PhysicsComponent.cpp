#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(void)
{
}


PhysicsComponent::~PhysicsComponent(void)
{
}

void PhysicsComponent::update( float dT ) {
	
	kinematics.update(dT);
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