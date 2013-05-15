#include "PlaneCollider.h"


PlaneCollider::PlaneCollider(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, bool solid)
{
	p0 = vert0; //(vert0 + vert1 + vert2) / 3.0f;
	p1 = vert1;
	p2 = vert2;
	p3 = vert3;
	glm::vec3 tangent = vert1 - vert0;
	glm::vec3 bitangent = vert2 - vert0;
	norm = glm::cross( tangent, bitangent );
	isSolid = solid;
}


PlaneCollider::~PlaneCollider(void)
{
}

glm::vec3 PlaneCollider::getNormal( ) {
	return norm;
}

glm::vec3* PlaneCollider::getFace(){
	glm::vec3 face[4];
	face[0] = p0;
	face[1] = p1;
	face[2] = p2;
	face[3] = p3;
	return face;
}

glm::vec3 PlaneCollider::getPointOnPlane(){
	return p0;
}

bool PlaneCollider::isSolidPlane(){
	return isSolid;
}