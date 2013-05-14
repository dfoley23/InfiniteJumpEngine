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
	if ( plane != NULL && direction != glm::vec3(0,0,0) ){
		glm::vec3 normal = glm::normalize(plane->getNormal());
		glm::vec3 Pp = plane->getPointOnPlane();
		float denom = glm::dot( normal, direction );
		//t = d - p0 dot n_ / d_ dot n_
		if (denom != 0.0f){
			float d = glm::dot( normal, Pp );
			time = (d - glm::dot( normal, rayStart )) / denom;
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