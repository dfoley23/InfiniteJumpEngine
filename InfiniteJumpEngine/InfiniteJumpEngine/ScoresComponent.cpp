#include "ScoresComponent.h"


ScoresComponent::ScoresComponent(void)
{
	firstHole = 0;
	lastHole = -1;
	profileName = "default.sav";
}


ScoresComponent::~ScoresComponent(void)
{
}

void ScoresComponent::loadProfile(char* filename)
{
	ifstream proFile;
	proFile.open (filename);
	if (!proFile.fail()){
		int numHoles;
		proFile >> numHoles;
		loadHoles(numHoles);
		score s;
		for (int i = 0; i < numHoles && i < highScores.size(); i++){
			proFile >> s;
			highScores[i] = s;
		}
		proFile.close();		
		cout << "Loading profile:" << filename << endl;
	} else {
		cerr << "Failed to open profile for reading:" << filename;
	}
}

void ScoresComponent::saveProfile(char* filename)
{
	ofstream proFile;
	proFile.open (filename);
	if (!proFile.fail()){
		int numHoles = highScores.size();
		proFile << numHoles << endl;
		score s;
		for (int i = 0; i < numHoles; i++){
			s = highScores[i];
			proFile << s << endl;
		}
		proFile.close();
		cout << "Saving profile:" << filename << endl;
	} else {
		cerr << "Failed to open profile for writing:" << filename;
	}
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