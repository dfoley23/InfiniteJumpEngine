#include "KinematicComponent.h"


KinematicComponent::KinematicComponent(void)
{
	
}

KinematicComponent::~KinematicComponent(void){
}

glm::mat4 KinematicComponent::getTransform(){
	return loc.getTransform();
}

void KinematicComponent::update(float dT){
	vel = vel + (acc * dT);
	loc = loc + (vel * dT);
}

void KinematicComponent::applyImpulse( glm::vec3 impulse ) {
	acc = impulse;
}

void KinematicComponent::receiveMessage( IJMessage *m){
	if (!m->getContent().compare("translate")
		|| !m->getContent().compare("rotate")
		|| !m->getContent().compare("scale")
		)
	{
		sendMessage(m, &loc);
	}
}