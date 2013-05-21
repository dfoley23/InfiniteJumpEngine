#pragma once
#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H
#include "Collider.h"

class SphereCollider :
	public Collider
{
public:
	SphereCollider(void);
	~SphereCollider(void);
protected:
	glm::vec3 center;
	glm::vec3 rad;
};

#endif SPHERE_COLLIDER_H