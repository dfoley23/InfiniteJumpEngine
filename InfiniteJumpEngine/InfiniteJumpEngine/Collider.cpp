#include "Collider.h"


Collider::Collider(void)
{
}


Collider::~Collider(void)
{
}

/**
* @param
* point to check
* three points of a triangle
**/
bool Collider::sameSideOfLine( glm::vec3 point, glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2 ) {
	glm::vec3 tangent = vert1 - vert0;
	glm::vec3 bitangent = vert2 - vert0;
	glm::vec3 pA = point - vert0;
	glm::vec3 pointNorm = glm::cross( tangent, pA );
	glm::vec3 norm = glm::cross( tangent, bitangent );
	if ( glm::dot( pointNorm, norm ) >= 0 ) {
		return true;
	}
	return false;
}

bool Collider::isCollidingRecursive(Collider* that){
	if (b_parentCollider && !dynamic_cast<Collider*>(parent)->isCollidingRecursive(that)){
		return false;
	}
	if (that->b_parentCollider && !isCollidingRecursive(dynamic_cast<Collider*>(that->parent))){
		return false;
	}
	return isColliding(that);
}

pair<bool,float> Collider::predictCollisionRecursive(Collider* that){
	if (b_parentCollider && !dynamic_cast<Collider*>(parent)->predictCollisionRecursive(that).first){
		return pair<bool,float>(false, 0.0f);
	}
	if (that->b_parentCollider && !predictCollisionRecursive(dynamic_cast<Collider*>(that->parent)).first){
		return pair<bool,float>(false, 0.0f);
	}
	return predictCollision(that);
}