#include "PhysicsComponent.h"


const int PhysicsComponent::COLLISION_CHECKS = 5;

/*  physics component updates kinematics
*   and checks collision data
*/
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

/*
* removes the physics component from memory
*/
PhysicsComponent::~PhysicsComponent(void)
{
	vector<PlaneCollider*>().swap(collisionData);
	delete &kinematics;
	delete mainCollider;
}

/*
*sums up all forces and integrates physics
*/
void PhysicsComponent::update( float dT ) {
	//get friction data
	glm::vec3 f = kinematics.vel.getPosition() * cFriction;
	//f.y = 0.0f;
	friction.setVector( f );
	//sum up friction and other forces
	glm::vec3 sumOfForces = glm::vec3(0,0,0);
	for (forceIter i = forces.begin(); i != forces.end(); i++){
		(*i)->update(dT);
		sumOfForces += (*i)->getValue();
	}

	//apply the force to kinematics
	kinematics.applyImpulse( sumOfForces );
	//check for collisions
	checkCollisionData( dT );
	//update velocity and position
	kinematics.update(dT);
}

/*
* checks the collision data
*/
void PhysicsComponent::checkCollisionData(float dT) {
	pair<bool, double> intersect;
	pair<bool, double> closestIntersect = pair<bool, double>(false,0.0f);
	PlaneCollider* closest = NULL;
	PlaneCollider* lastClosest = NULL;
	bool hitUnSolidPlane = false;
	//checks for multiple collisions
	for (int check = 0; 
		check < COLLISION_CHECKS 
		&& (check == 0 
		|| (closest != lastClosest)); 
	check++)
	{
		lastClosest = closest;
		closest = NULL;
		closestIntersect.first = false;
		//build a ray from the object in the direction of the velocity
		mainCollider->setRayStart( kinematics.loc.getPosition() );
		mainCollider->setDirection( kinematics.vel.getPosition() );
		//using this ray check intersection with all the collision data
		for (colliderIter cIter = collisionData.begin();  cIter != collisionData.end(); ++cIter ) {
			//predict the intersection using the appropirate equations for the type of collision data
			intersect = mainCollider->predictIntersection((*cIter));
			//if intersection time is not zero and is less than one time step 
			//than the ray will intersect with the plane in the next time step
			if ( intersect.first && abs(intersect.second) < dT ) {
				//if this time is less than any other calculated intersection 
				if ( !closestIntersect.first 
					|| abs(intersect.second) < abs(closestIntersect.second) )
				{
					//if this is either a solid plane (wall) 
					//or the ray hasnt intersected a nonsolid object yet
					//then set this intersection as the closest
					//this makes sure that you only collide with one unsolid plane
					if ( !hitUnSolidPlane || (*cIter)->isSolidPlane() ) 
					{
						closest = (*cIter);
						closestIntersect = intersect;
					}
				}
			}
		}
		//once you have found a closest intersection
		//extract collision normal 
		//and do appropriate calculations ie reflect other collision behaviour
		if ( closest ){
			if ( !closest->isSolidPlane() ) { 
				hitUnSolidPlane = true;
			}
			//update the kinematics to half the intersection time 
			kinematics.update((float)closestIntersect.second/2.0f);
			sendMessage( closest, getParent(), "InterSection", glm::vec4( closest->getNormal(), 1.0f) );
			sendMessage( getParent(), closest, "InterSection", glm::vec4( closest->getNormal(), 1.0f) );
			//decrement delta time and check for collisions in this delta time
			//this ensures that after a reflection off a wall that you wont over step another collision
			dT -= (float)closestIntersect.second/2.0f;
		}
	}

}

/*
* sets the collider that checks collisions against all other objects
*/
void PhysicsComponent::setMainCollider( RayCollider * collider){ 
	mainCollider = collider;
}

/*
* add more collision data to check against the main collider
*/
void PhysicsComponent::addCollider(PlaneCollider* collider){ 
	this->collisionData.push_back( collider );
}

void tileCollision(Contact* contact){

}

void wallCollision(Contact* contact){

}

void cupCollision(Contact* contact){

}