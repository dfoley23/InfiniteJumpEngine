#include "ScoresComponent.h"


ScoresComponent::ScoresComponent(void)
{
	firstHole = 0;
	lastHole = -1;
	profileName = "default";
}


ScoresComponent::~ScoresComponent(void)
{
	//saveProfile(profileName);
}

void ScoresComponent::loadProfile(char* filename)
{
	/*
	ifstream proFile;
	proFile.open (filename);
	int numHoles;
	proFile >> numHoles;
	loadHoles(numHoles);
	score s;
	for (int i = 0; i < numHoles && i < highScores.size(); i++){
		proFile >> s;
		highScores[i] = s;
	}
	proFile.close();
	strcpy(profileName, filename);
	*/
}

void ScoresComponent::saveProfile(char* filename)
{
	/*
	ofstream proFile;
	proFile.open (filename);
	proFile << highScores.size();
	for (int i = 0; i < highScores.size(); i++){
		proFile << highScores.at(i);
	}
	proFile.close();
	*/
}

void ScoresComponent::loadHoles(holeID last)
{
	lastHole = last;
	pars.resize(last);
	currentScores.resize(last);
	highScores.resize(last);
}

score ScoresComponent::getTotalScore(holeID i)
{
	score total = 0;
	for (holeID i = firstHole+1; i < lastHole; i++){
		total = total + currentScores[i] - pars[i];
	}
	return total;
}

score ScoresComponent::getTotalHighScore(holeID i)
{
	score total = 0;
	for (holeID i = firstHole+1; i < lastHole; i++){
		total = total + highScores[i] - pars[i];
	}
	return total;
}

holeID ScoresComponent::getBestHole()
{
	holeID id = firstHole;
	score best = highScores[firstHole];
	for (holeID i = firstHole+1; i < lastHole; i++){
		if (highScores[i] < best || (pars[i] > pars[id])){
			id = i;
			best = highScores[i];
		}
	}
	return id;
}

holeID ScoresComponent::getCurrentBestHole()
{
	holeID id = firstHole;
	score best = currentScores[firstHole];
	for (holeID i = firstHole+1; i < lastHole; i++){
		if (currentScores[i] < best || (pars[i] > pars[id])){
			id = i;
			best = currentScores[i];
		}
	}
	return id;
}

holeID ScoresComponent::getWorstHole()
{
	return -1;
}

holeID ScoresComponent::getCurrentWorstHole()
{
	return -1;
}