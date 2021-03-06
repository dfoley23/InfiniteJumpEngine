#pragma once
#ifndef MESH_COLLIDER_H
#define MESH_COLLIDER_H
#include "Collider.h"

class MeshCollider :
	public Collider
{
public:
	MeshCollider(Mesh*);
	~MeshCollider(void);

	bool isColliding(BoxCollider*);
	bool isColliding(SphereCollider*);
	bool isColliding(MeshCollider*);

	pair<bool,float> predictCollision(BoxCollider*);
	pair<bool,float> predictCollision(SphereCollider*);
	pair<bool,float> predictCollision(MeshCollider*);

	Mesh * getMesh( );
protected:
	Mesh* mesh;
};

#endif MESH_COLLIDER_H