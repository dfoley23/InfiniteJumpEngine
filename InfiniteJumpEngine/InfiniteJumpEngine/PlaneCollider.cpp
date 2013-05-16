#include "PlaneCollider.h"


PlaneCollider::PlaneCollider(glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, bool solid)
{
	face.push_back( vert0 ); //(vert0 + vert1 + vert2) / 3.0f;
	face.push_back( vert1 ); 
	face.push_back( vert2 ); 
	face.push_back( vert3 ); 
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

glm::vec3 PlaneCollider::getPointOnPlane() {
	return face[0];
}

vector<glm::vec3> PlaneCollider::getFace(){
	return face;
}

glm::vec3 PlaneCollider::getIntersectionPoint(){
	return intersect;
}

void PlaneCollider::setInterSectionPoint( glm::vec3 cX ){
	intersect = cX;
}

bool PlaneCollider::isSolidPlane(){
	return isSolid;
}