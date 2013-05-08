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

protected:
	PositionComponent* position;
	glm::vec3 dim;
};

#endif