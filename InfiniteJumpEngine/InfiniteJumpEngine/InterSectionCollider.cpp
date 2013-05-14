#include "InterSectionCollider.h"


InterSectionCollider::InterSectionCollider()
{
	direction = glm::vec3( 0, 0, 0);
	rayStart = glm::vec3( 0, 0, 0);
	time = 0.0f;
}


InterSectionCollider::~InterSectionCollider(void)
{
}

pair<bool, double> InterSectionCollider::predictIntersection( glm::vec3 vert0, glm::vec3 vert1, glm::vec3 normal ) {
	float denom = glm::dot( normal, direction );
	if (denom != 0.0f){
		time = (glm::dot( normal, vert0 ) - glm::dot( normal, rayStart )) / glm::dot( normal, direction );
		return pair<bool,double>(true, time);
	}
	return pair<bool,double>(false, 0.0f);
}

void InterSectionCollider::setDirection( glm::vec3 dir ) {
	direction = dir;
}

void InterSectionCollider::setRayStart( glm::vec3 start ) {
	rayStart = start;
}

double InterSectionCollider::getInterSectTime( ) {
	return time;
}