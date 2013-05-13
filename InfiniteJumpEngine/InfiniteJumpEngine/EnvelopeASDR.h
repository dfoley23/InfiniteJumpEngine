#include "Component.h"
#pragma once
class EnvelopeASDR : public Component
{
public:
	EnvelopeASDR(float a, float aT, float dT, float s, float sT, float rT);
	~EnvelopeASDR(void);
	void start();
	void stop();
	void update(float dT);
	float getValue();
	static const float MIN_T;
protected:
	float attack;
	float attackTime;
	float decayTime;
	float sustain;
	float sustainTime;
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

