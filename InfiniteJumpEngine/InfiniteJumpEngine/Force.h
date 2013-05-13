#pragma once
#include "Component.h"
#include "EnvelopeASDR.h"

class Force :
	public Component
{
public:
	Force(glm::vec3, float t = 0.0f, bool i = true); //Returns an impulse
	~Force(void);
	glm::vec3 getValue(){return force*envelope.getValue();}
	void start();
	void stop();
	void update(float dT);
protected:
	glm::vec3 force;
	EnvelopeASDR envelope;
	bool b_impulse;
};

