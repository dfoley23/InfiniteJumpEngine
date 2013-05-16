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
		vector<glm::vec3> face = plane->getFace();
		glm::vec3 p0 = face[0];
		glm::vec3 p1 = face[1];
		glm::vec3 p2 = face[2];
		glm::vec3 p3 = face[3];
		float denom = glm::dot( normal, direction );
		//t = d - p0 dot n_ / d_ dot n_
		if (denom > 0.0f){
			//time = (glm::dot( normal, p0 ) - glm::dot( normal, direction )) / glm::dot( normal, direction );
			float d = glm::dot( normal, p0);
			time = (d - glm::dot( normal, rayStart )) / denom;
			glm::vec3 cX = rayStart + (direction * (float)time);
			plane->setInterSectionPoint( cX );

			if ( ( sameSideOfLine( cX, p0, p1, p2 )
				&& sameSideOfLine( cX, p1, p2, p0 )
				&& sameSideOfLine( cX, p2, p0, p1 ) )
				|| ( sameSideOfLine( cX, p0, p2, p3 )
				&& sameSideOfLine( cX, p2, p3, p0 )
				&& sameSideOfLine( cX, p3, p0, p2 ) ) ) 
			{
				return pair<bool,double>(true, time);
			} 
			return pair<bool, double>(false, 0.0f);
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