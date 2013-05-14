#pragma once
#ifndef INTERSECTION_COLLIDER_H
#define INTERSECTION_COLLIDER_H
#include "glIncludes.h"
#include "Collider.h"

class InterSectionCollider : public Collider
{
public:
	InterSectionCollider( );
	~InterSectionCollider(void);

	pair<bool, double> predictIntersection( glm::vec3, glm::vec3, glm::vec3 );

	void setDirection( glm::vec3 );
	void setRayStart( glm::vec3 );
	double getInterSectTime( );
	glm::vec3 p0;
	glm::vec3 p1;
private:
	glm::vec3 direction;
	glm::vec3 rayStart;
	double time;
};

#endif