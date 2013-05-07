#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
class TransformComponent: public Component
{
public:
	TransformComponent(void){};
	~TransformComponent(void){};

	//Combine transformations
	virtual glm::mat4 getTransform()=0;
	virtual glm::mat4 transform(glm::mat4 in){
		if (parent)
			in = parent->transform(in);
		in *= getTransform();
		return in;
	}
};

#endif

;
