#pragma once
#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable
{
public:
	virtual void update(float dT){};
	virtual long updateOrder(){ return 0; };
	virtual bool compareUpdateOrder(){ return false; };
};

#endif // ENTITY_H