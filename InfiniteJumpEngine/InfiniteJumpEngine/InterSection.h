#pragma once
#ifndef INTER_SECTION_H
#define INTER_SECTION_H
#include "glIncludes.h"
#include "PlaneCollider.h"

class InterSection
{
	PlaneCollider * plane;
	double time;
public:
	InterSection( double time, PlaneCollider * plane);
	~InterSection(void);

	PlaneCollider * getPlane( );
	double getInterSectTime( ) const{
		return time;
	}
};

#endif INTER_SECTION_H