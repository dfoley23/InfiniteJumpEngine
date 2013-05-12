#include "Collider.h"


Collider::Collider(void)
{
}


Collider::~Collider(void)
{
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