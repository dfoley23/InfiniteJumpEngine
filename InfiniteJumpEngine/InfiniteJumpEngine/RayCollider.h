#pragma once
#ifndef RAY_COLLIDER_H
#define RAY_COLLIDER_H
#include "glIncludes.h"
#include "Collider.h"
#include "PlaneCollider.h"

class RayCollider : public Collider
{
public:
	RayCollider( );
	~RayCollider(void);

	pair<bool, double> predictIntersection( PlaneCollider * plane );

	void setDirection( glm::vec3 );
	void setRayStart( glm::vec3 );
	glm::vec3 getRayStart(){return rayStart;}
	double getInterSectTime( );
private:
	glm::vec3 direction;
	glm::vec3 rayStart;
	double time;
};

#endif RAY_COLLIDER_H