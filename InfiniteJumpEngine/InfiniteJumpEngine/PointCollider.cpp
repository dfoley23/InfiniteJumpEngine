#include "PointCollider.h"


PointCollider::PointCollider(glm::vec3 p)
{
	point = p;
}


PointCollider::~PointCollider(void)
{
}

bool PointCollider::isColliding(BoxCollider* that)
{
	glm::vec3 box = that->getPos();
	glm::vec3 dim = that->getDim();
	if ( point.x > box.x
		&& point.y > box.y
		&& point.z > box.z
		&& point.x < dim.x
		&& point.y < dim.y
		&& point.z < dim.z ) {
			return true;
	}
	return false;
}

bool PointCollider::isColliding(SphereCollider* that)
{
	return false;
}

bool PointCollider::isColliding(MeshCollider* that)
{
	vector<float> verts = that->getMesh()->getVerts();
	glm::vec3 vert0;
	glm::vec3 vert1;
	glm::vec3 vert2;
	point.y = 0;
	int i = 0;
	while( i < static_cast<int>(verts.size())-9 ) {
		vert0 = glm::vec3( verts.at(i), 0, verts.at(i+2) );
		vert1 = glm::vec3( verts.at(i+3), 0, verts.at(i+5) );
		vert2 = glm::vec3( verts.at(i+6), 0, verts.at(i+8) );
		if ( 
			//inTriangleBounds( point-vert0, point-vert1, point-vert2 )
			sameSideOfLine( point, vert0, vert1, vert2 ) 
			&& sameSideOfLine( point, vert1, vert0, vert2)
			&& sameSideOfLine( point, vert2, vert1, vert0) 
			) {
				sendMessage( this->getParent(), that, "MeshCollision", glm::vec3( 0, 0, 0) );
				return true;
		}
		i+=9;
	}
	return false;
}

void PointCollider::setPointPos( glm::vec3 pos ){
	point = pos;
}

pair<bool,float> PointCollider::predictCollision(BoxCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}

pair<bool,float> PointCollider::predictCollision(SphereCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}

pair<bool,float> PointCollider::predictCollision(MeshCollider* that)
{
	return pair<bool,float>(false, 0.0f);
}