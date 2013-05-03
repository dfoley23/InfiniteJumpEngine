#pragma once
#ifndef POSITION_H
#define POSITION_H

#include "Component.h"
class PositionComponent: public Component
{
public:
	PositionComponent(void){};
	~PositionComponent(void){};
	virtual glm::vec3 getPosition()=0;
	virtual void setPosition(glm::vec3)=0;
	virtual void setPosition(float, float, float)=0;
	virtual glm::mat4 getTransformation()=0;
};

#endif

;
