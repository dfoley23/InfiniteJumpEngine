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
	//cout << "point : " << point.x << point.y << point.z << endl;
	//cout << "min : " << box.x << box.y << box.z << endl;
	//cout << "max : " << dim.x << dim.y << dim.z << endl;
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
	glm::vec3 minXPoint = that->getMesh()->getMinXPoint();
	glm::vec3 minYPoint = that->getMesh()->getMinXPoint();
	glm::vec3 minZPoint = that->getMesh()->getMinXPoint();
	glm::vec3 maxXPoint = that->getMesh()->getMaxXPoint();
	glm::vec3 maxYPoint = that->getMesh()->getMaxYPoint();
	glm::vec3 maxZPoint = that->getMesh()->getMaxZPoint();
	//if ( point.x > that->getMesh() ) {

	}
	return false;
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