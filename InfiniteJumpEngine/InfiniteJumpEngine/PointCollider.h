#pragma once
#ifndef POINT_COLLIDER_H
#define POINT_COLLIDER_H
#include "glIncludes.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "Mesh.h"

class SphereCollider;

class PointCollider :
	public Collider
{
public:
	PointCollider(glm::vec3 point);
	~PointCollider(void);

	bool isColliding(BoxCollider*);
	bool isColliding(SphereCollider*);
	bool isColliding(MeshCollider*);

	void setPointPos( glm::vec3 pos );
	pair<bool,float> predictCollision(BoxCollider*);
	pair<bool,float> predictCollision(SphereCollider*);
	pair<bool,float> predictCollision(MeshCollider*);

	glm::vec3 point;
protected:
};

#endif POINT_COLLIDER_H