#pragma once
#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Collider.h"
#include "SphereCollider.h"
#include "MeshCollider.h"
#include "PositionComponent.h"

class MeshCollider;
class SphereCollider;

class BoxCollider :
	public Collider
{
public:
	BoxCollider(void);
	~BoxCollider(void);

	bool isColliding(BoxCollider*);
	bool isColliding(SphereCollider*);
	bool isColliding(MeshCollider* that);

	pair<bool,float> predictCollision(BoxCollider*);
	pair<bool,float> predictCollision(SphereCollider*);
	pair<bool,float> predictCollision(MeshCollider* that);

	glm::vec3 getDim( );
	glm::vec3 getPos();
	void setDim( glm::vec3 dimension );
	void setPos( glm::vec3 pos );
protected:
	glm::vec3 position;
	glm::vec3 dim;
};

#endif