#include "PlaneCollider.h"


PlaneCollider::PlaneCollider(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2)
{
	point = (vert0 + vert1 + vert2) / 3.0f;
	glm::vec3 tangent = vert1 - vert0;
	glm::vec3 bitangent = vert2 - vert0;
	norm = glm::cross( tangent, bitangent );
}


PlaneCollider::~PlaneCollider(void)
{
}

glm::vec3 PlaneCollider::getNormal( ) {
	return norm;
}

glm::vec3 PlaneCollider::getPointOnPlane(){
	return point;
}