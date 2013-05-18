#pragma once
#include "Component.h"
#include "EnvelopeASDR.h"

class Force :
	public Component
{
public:
	Force(glm::vec3 = glm::vec3(0,0,0), float t = 0.0f, bool i = false); //Returns an impulse
	~Force(void);
	glm::vec3 getValue(){return force*envelope.getValue();}
	void start();
	void stop();
	void update(float dT);
	inline void setForceVector(glm::vec3 f){force = f;}
	inline void setEnvelope(EnvelopeASDR e){envelope = e;}
protected:
	glm::vec3 force;
	EnvelopeASDR envelope;
	bool b_impulse;
};

