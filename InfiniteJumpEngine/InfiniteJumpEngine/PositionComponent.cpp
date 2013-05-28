#include "PositionComponent.h"


PositionComponent::PositionComponent(glm::vec3 n_pos, glm::vec4 n_rot, glm::vec3 n_sca)
{
	setPosition(n_pos);
	setRotation(n_rot);
	setScale(n_sca);
}


PositionComponent::~PositionComponent(void)
{
}

/*
* gets all of the transformations after kinematics have
* caused transformations
*/
glm::mat4 PositionComponent::getTransform(){
	glm::mat4 t = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 r;
	if ( rotation.x > 0.f || rotation.y > 0.f || rotation.z > 0.f || rotation.w > 0.f ) {
		r = glm::rotate( glm::mat4(), rotation.w, glm::vec3( rotation.x, rotation.y, rotation.z ) );
	} else
	{
		glm::mat4 rX = glm::rotate( glm::mat4( ), rotation.x, glm::vec3( 1, 0, 0 ) );
		glm::mat4 rY = glm::rotate( glm::mat4( ), rotation.y, glm::vec3( 0, 1, 0 ) );
		glm::mat4 rZ = glm::rotate( glm::mat4( ), rotation.z, glm::vec3( 0, 0, 1 ) );
		r = rX * rY * rZ;
	}
	glm::mat4 s = glm::scale(glm::mat4(1.0f), scale);
	return t * r * s;
}

glm::vec3 PositionComponent::getPosition() {
	return position;
}

glm::vec4  PositionComponent::getRotation() {
	return rotation;
}

const PositionComponent PositionComponent::operator+(const PositionComponent &that){
	PositionComponent out;
	out.position = position + that.position;
	out.rotation = rotation + that.rotation;
	out.scale = scale + that.scale;
	return out;
}

const PositionComponent PositionComponent::operator*(const float scalar){
	PositionComponent out;
	out.position = position * scalar;
	out.rotation = rotation * scalar;
	out.scale = scale * scalar;
	return out;
}

void PositionComponent::receiveMessage( IJMessage *m){
	if (!m->getContent().compare("translate")){
		position = m->getVector().xyz;
	} else if (!m->getContent().compare("rotate")){
		rotation = m->getVector();
	} else if (!m->getContent().compare("scale")){
		scale = m->getVector().xyz;
	}
}