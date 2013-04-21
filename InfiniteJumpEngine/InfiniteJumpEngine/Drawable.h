#pragma once
#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Updatable.h"
#include "Camera.h"

class Drawable : public Updatable
{
public:
	virtual void draw(Camera *){};
	virtual long drawOrder(){ return 0; };
	virtual bool compareDrawOrder(){ return false; };
};

#endif // ENTITY_H