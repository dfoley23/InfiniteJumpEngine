#include "Force.h"

Force::Force(glm::vec3 vec, float time, bool i):
	envelope(1.0f, 0.0f, 0.0f, 1.0f, time, 0.0f)	
{
	force = vec;
	b_impulse = i;
}

Force::~Force(void)
{
}

void Force::start(){
	envelope.start();
	if (b_impulse)
		envelope.stop();
}

void Force::stop(){
	envelope.stop();
}

void Force::update(float dT){
	envelope.update(dT);
}