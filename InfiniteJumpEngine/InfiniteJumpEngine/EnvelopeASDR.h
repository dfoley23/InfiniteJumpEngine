#include "Component.h"
#pragma once
class EnvelopeASDR : public Component
{
public:
	EnvelopeASDR(float a, float aT, float dT, float s, float sT, float rT);
	~EnvelopeASDR(void);
	void start();
	void stop();
	void setHold(bool v){hold = v;}
	void update(float dT);
	float getValue();
	static const float MIN_T;
protected:
	//Initial value that the envelope spikes to when first activated.
	float attack;
	//Amount of time it takes to reach the attack's peak.
	float attackTime;
	//Amount of time between the attack peak and the sustain state.
	float decayTime;
	//Value of the envelope while sustaining.
	float sustain;
	//Minimum time to hold the sustain value.
	float sustainTime;
	//Time from release to zero state.
	float releaseTime;
	/*
	 * 0 = inactive
	 * 1 = attack
	 * 2 = decay
	 * 3 = sustain
	 * 4 = release
	 */
	int state;
	float time;
	bool hold;
};

