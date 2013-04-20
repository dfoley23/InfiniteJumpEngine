#pragma once
#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

class Mesh; class Entity; class Camera;

class EntityComponent
{
public:
	virtual void update(float dT){};
	virtual void draw( Camera * camera ){};
	virtual Entity * getParent(){return parent;};
	virtual void setParent(Entity * p){parent = p;};
	virtual long updateOrder(){ return 0; };
	virtual long drawOrder(){ return 0; };
	virtual bool compareUpdateOrder(){ return false; };
	virtual bool compareDrawOrder(){ return false; };
protected:
	Entity *parent;
};

#endif // ENTITY_H
