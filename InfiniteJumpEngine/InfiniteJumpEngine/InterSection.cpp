#include "InterSection.h"


InterSection::InterSection( double t, PlaneCollider * p )
{
	plane = p;
	time = t;
}


InterSection::~InterSection(void)
{
}

PlaneCollider * InterSection::getPlane( ) {
	return plane;
}
