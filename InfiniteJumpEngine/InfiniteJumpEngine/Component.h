#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include "Drawable.h"
#include <vector>

class Game;

class Component: public Drawable
{
public:
	virtual Component * getParent(){return parent;};
	virtual void setParent(Component * p){parent = p;};
	virtual Game *getGame(){
		if (getParent())
			return getParent()->getGame();
		return NULL;
	}
protected:
	Component *parent;
};

typedef std::vector<Component*> componentVector;
typedef componentVector::iterator componentIter;

#endif // ENTITY_H
