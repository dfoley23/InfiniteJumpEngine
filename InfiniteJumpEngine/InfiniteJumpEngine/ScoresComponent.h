#ifndef SCORE_COMPONENT_H
#define SCORE_COMPONENT_H
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

typedef int score;
typedef int holeID;
typedef vector<score> ScoreContainer;
typedef ScoreContainer::iterator scoreIter;

class ScoresComponent
{
public:
	ScoresComponent(void);
	~ScoresComponent(void);
	inline bool validHole(holeID i){return (i >= firstHole && i < lastHole);}
	inline score getCurrentScore(holeID i){return validHole(i)? currentScores[i]:NO_SCORE;}
	inline score getHighScore(holeID i){return validHole(i)? highScores[i]:NO_SCORE;}
	inline void setCurrentScore(holeID i, score s){if (validHole(i)) currentScores[i] = s;}
	inline void setHighScore(holeID i, score s){if (validHole(i)) highScores[i] = s;}
	inline void registerScore(holeID i, score s){
		setCurrentScore(i,s);
		setHighScore(i, std::min(s, highScores[i]>0? highScores[i]:s));
	}
	void loadProfile(char*);
	void saveProfile(char*);
	void loadHoles(holeID);
	score getTotalScore(holeID i);
	score getTotalHighScore(holeID i);
	holeID getBestHole();
	holeID getCurrentBestHole();
	holeID getWorstHole();
	holeID getCurrentWorstHole();
	static const int NO_SCORE = -1;
protected:
	ScoreContainer pars;
	ScoreContainer currentScores;
	ScoreContainer highScores;
	holeID firstHole;
	holeID lastHole;
	char* profileName;
};

#endif

