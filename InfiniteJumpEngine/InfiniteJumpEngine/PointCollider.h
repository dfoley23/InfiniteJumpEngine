#pragma once
#ifndef POINT_COLLIDER_H
#define POINT_COLLIDER_H
#include "glIncludes.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

class BoxCollider;
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

	pair<bool,float> predictCollision(BoxCollider*);
	pair<bool,float> predictCollision(SphereCollider*);
	pair<bool,float> predictCollision(MeshCollider*);
	
	glm::vec3 point;
protected:
};

#endif