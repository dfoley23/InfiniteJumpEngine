#pragma once
#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

class MeshBatch; class Entity;

class EntityComponent
{
public:
	virtual void update(float dT){};
	virtual void draw( MeshBatch *batch ){};
	virtual Entity * getParent(){return parent;};
	virtual void setParent(Entity * p){parent = p;};
	virtual long updateOrder();
	virtual long drawOrder();
	virtual bool compareUpdateOrder();
	virtual bool compareDrawOrder();
protected:
	Entity *parent;
};

#endif // ENTITY_H
