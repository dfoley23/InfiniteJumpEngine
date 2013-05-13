#include "IJTime.h"


IJTime::IJTime(void)
{
	reset();
}


IJTime::~IJTime(void)
{
}

const IJTime IJTime::operator-(const IJTime& that){
	IJTime out;
	out.internal = internal - that.internal;
	return out;
}