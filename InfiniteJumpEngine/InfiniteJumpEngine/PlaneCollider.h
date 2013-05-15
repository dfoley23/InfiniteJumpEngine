#pragma once
#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H
#include "glIncludes.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "MeshCollider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider( glm::vec3, glm::vec3, glm::vec3, glm::vec3, bool );
	~PlaneCollider(void);


	bool isColliding(BoxCollider*);
	bool isColliding(SphereCollider*);
	bool isColliding(MeshCollider*);

	pair<bool,float> predictCollision(BoxCollider*);
	pair<bool,float> predictCollision(SphereCollider*);
	pair<bool,float> predictCollision(MeshCollider*);

	glm::vec3 getNormal( );

	glm::vec3* getFace();

	glm::vec3 getPointOnPlane();

	bool isSolidPlane();

private:
	bool isSolid;
	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 norm;
};

#endif RAY_COLLIDER_H