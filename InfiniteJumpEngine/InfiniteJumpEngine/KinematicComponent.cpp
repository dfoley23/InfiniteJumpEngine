#include "KinematicComponent.h"


KinematicComponent::KinematicComponent(void): position(0.f,0.f,0.f)
{
	
}

glm::mat4 KinematicComponent::getTransform(){
	return glm::translate(glm::mat4(), position);
}