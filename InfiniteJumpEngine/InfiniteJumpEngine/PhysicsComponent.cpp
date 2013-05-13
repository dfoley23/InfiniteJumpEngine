#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(void)
{
	kinematics.setParent( this );
}


PhysicsComponent::~PhysicsComponent(void)
{
}

void PhysicsComponent::update( float dT ) {
	glm::vec3 sumOfForces = glm::vec3(0,0,0);
	for (forceIter i = forces.begin(); i != forces.end(); i++){
		(*i)->update(dT);
		sumOfForces += (*i)->getValue();
	}
	kinematics.applyImpulse( sumOfForces );
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