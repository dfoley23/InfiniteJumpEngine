#include "BoxCollider.h"


BoxCollider::BoxCollider(void)
{
}


BoxCollider::~BoxCollider(void)
{
}

bool BoxCollider::isColliding(BoxCollider* that)
{
	return false;
}

bool BoxCollider::isColliding(SphereCollider* that)
{
	return false;
}

bool BoxCollider::isColliding(MeshCollider* that)
{
	return false;
}

pair<bool,float> BoxCollider::predictCollision(BoxCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}

pair<bool,float> BoxCollider::predictCollision(SphereCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}

pair<bool,float> BoxCollider::predictCollision(MeshCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}

glm::vec3 BoxCollider::getPos() {
	return position;
}

glm::vec3 BoxCollider::getDim(){
	return dim;
}
