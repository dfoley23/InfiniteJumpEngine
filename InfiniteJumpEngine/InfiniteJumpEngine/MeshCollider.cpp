#include "MeshCollider.h"


MeshCollider::MeshCollider(Mesh* n_mesh)
{
	mesh = n_mesh;
}


MeshCollider::~MeshCollider(void)
{
}

bool MeshCollider::isColliding(BoxCollider* that)
{
	return false;
}

bool MeshCollider::isColliding(SphereCollider* that)
{
	return false;
}

bool MeshCollider::isColliding(MeshCollider* that)
{
	return false;
}

bool MeshCollider::isColliding(PointCollider* that)
{
	return false;
}

pair<bool,float> MeshCollider::predictCollision(BoxCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}

pair<bool,float> MeshCollider::predictCollision(SphereCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}

pair<bool,float> MeshCollider::predictCollision(MeshCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}