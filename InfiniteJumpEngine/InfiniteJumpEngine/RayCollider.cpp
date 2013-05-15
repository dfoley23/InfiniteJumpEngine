#include "RayCollider.h"


RayCollider::RayCollider()
{
	direction = glm::vec3( 0, 0, 0);
	rayStart = glm::vec3( 0, 0, 0);
	time = 0.0f;
}


RayCollider::~RayCollider(void)
{
}

pair<bool, double> RayCollider::predictIntersection( PlaneCollider * plane ) {
	if ( plane != NULL ) {
		glm::vec3 normal = plane->getNormal();
		glm::vec3 Pp = plane->getPointOnPlane();
		float denom = glm::dot( normal, direction );
		if (denom != 0.0f){
			time = (glm::dot( normal, Pp ) - glm::dot( normal, direction )) / glm::dot( normal, direction );
			return pair<bool,double>(true, time);
		}
	}
	return pair<bool,double>(false, 0.0f);
}

void RayCollider::setDirection( glm::vec3 dir ) {
	direction = dir;
}

void RayCollider::setRayStart( glm::vec3 start ) {
	rayStart = start;
}

double RayCollider::getInterSectTime( ) {
	return time;
}