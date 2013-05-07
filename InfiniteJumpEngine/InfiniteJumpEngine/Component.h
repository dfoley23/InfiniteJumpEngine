#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include "Drawable.h"
#include <vector>

class Component: public Drawable
{
public:
	virtual Component * getParent(){return parent;};
	virtual void setParent(Component * p){parent = p;};
	virtual glm::mat4 transform(void){
		return transform(glm::mat4());
	}
	virtual glm::mat4 transform(glm::mat4 in){
		if (parent)
			return parent->transform(in);
		return in;
	}
	virtual glm::vec3 getPickId( ) {
		return pickId;
	}

protected:
	Component *parent;
	glm::vec3 pickId;
};

typedef std::vector<Component*> componentVector;
typedef componentVector::iterator componentIter;

#endif // ENTITY_H
