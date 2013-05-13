#include "EnvelopeASDR.h"

const float EnvelopeASDR::MIN_T = 0.0001f;

EnvelopeASDR::EnvelopeASDR(float a, float aT, float dT, float s, float sT, float rT)
{
	attack = a;
	attackTime = aT;
	decayTime = dT;
	sustain = s;
	sustainTime = sT;
	releaseTime = rT;
	state = 0;
	hold = false;
}


EnvelopeASDR::~EnvelopeASDR(void)
{
}

void EnvelopeASDR::start()
{
	if (state == 0){
		hold = true;
		state = 1;
	}
}

void EnvelopeASDR::stop()
{
	hold = false;
}

void EnvelopeASDR::update(float dT){
	if (state == 1 && time >= attackTime){
		cout << "envelope state 1->2. time:" << time << endl;
		time = 0.0f;
		state = 2;
	} else if (state == 2 && time >= decayTime){
		cout << "envelope state 2->3. time:" << time << endl;
		time = 0.0f;
		state = 3;
	} else if (state == 3 && !hold && time >= sustainTime ){
		cout << "envelope state 3->4. time:" << time << endl;
		time = 0.0f;
		state = 4;
	} else if (state == 4 && time >= releaseTime){
		cout << "envelope state 4->0. time:" << time << endl;
		time = 0.0f;
		state = 0;
	}
	if (state == 0)
		time = 0.0f;
	else
		time += dT;
}

float EnvelopeASDR::getValue(){
	switch(state){
	case 1:
		if (attackTime < MIN_T)
			return attack;
		return attack*(time / attackTime);
	case 2:
		if (decayTime < MIN_T)
			return sustain;
		return sustain + (attack - sustain)*((decayTime - time)/decayTime);
	case 3:
		return sustain;
	case 4:
		if (releaseTime < MIN_T)
			return 0.0f;
		return sustain * ((releaseTime - time)/releaseTime);
	default:
		return 0.0f;
	}
}
