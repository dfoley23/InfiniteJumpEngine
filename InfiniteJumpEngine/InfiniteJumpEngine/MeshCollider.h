#pragma once
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
class MeshCollider :
	public Collider
{
public:
	MeshCollider(void);
	~MeshCollider(void);

	bool isColliding(BoxCollider*);
	bool isColliding(SphereCollider*);
	bool isColliding(MeshCollider*);

	pair<bool,float> predictCollision(BoxCollider*);
	pair<bool,float> predictCollision(SphereCollider*);
	pair<bool,float> predictCollision(MeshCollider*);
};

