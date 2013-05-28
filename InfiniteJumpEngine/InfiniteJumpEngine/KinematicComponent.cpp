#include "KinematicComponent.h"


KinematicComponent::KinematicComponent(void)
{
	acc = acc * 0;
	vel = vel * 0;
}

KinematicComponent::~KinematicComponent(void){
}

glm::mat4 KinematicComponent::getTransform(){
	return loc.getTransform();
}

/*
* integrates velocity and position
*/
void KinematicComponent::update(float dT){
	vel = vel + (acc * dT);
	loc = loc + (vel * dT);
}

/*
* applies a force impulse
*/
void KinematicComponent::applyImpulse( glm::vec3 impulse ) {
	acc.setPosition( impulse );
}

/*
* recieves messages to apply kinematics
*/
void KinematicComponent::receiveMessage( IJMessage *m){
	if (!m->getContent().compare("translate")
		|| !m->getContent().compare("rotate")
		|| !m->getContent().compare("scale")
		)
	{
		sendMessage(m, &loc);
	}
}