#pragma once
#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"

class TransformComponent: public Component
{
public:
	TransformComponent(void){};
	~TransformComponent(void){};

	//Combine transformations
	virtual glm::mat4 getTransform(){ return glm::mat4(1.0f); };
	virtual glm::mat4 transform(glm::mat4 in){
		if (parent)
			in = parent->transform(in);
		in *= getTransform();
		return in;
	}
};

#endif TRANSFORM_COMPONENT_H