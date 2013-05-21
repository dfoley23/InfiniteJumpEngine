#pragma once
#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H
#include <vector>
#include "glIncludes.h"
#include "Collider.h"

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

	vector<glm::vec3> getFace();

	glm::vec3 getIntersectionPoint();

	void setInterSectionPoint( glm::vec3 intersect );

	glm::vec3 getPointOnPlane();

	bool isSolidPlane();

private:
	bool isSolid;
	vector<glm::vec3> face;
	glm::vec3 norm;
	glm::vec3 intersect;
};

#endif PLANE_COLLIDER_H