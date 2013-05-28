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

/*
* Data structure class for holding minigolf scores. 
* Currently implemented in C++, but will probably be ported to Lua soon.
*
* Commenting by: Kevin Cameron
*/
class ScoresComponent
{
public:
	ScoresComponent(void); //Basic Constructor
	~ScoresComponent(void); //Basic Destructor
	//Is the given index a valid hole?
	inline bool validHole(holeID i){return (i >= firstHole && i < lastHole);}
	/* 
	* Return the current score for the hole.
	* This is subject to change over multiple playthroughs and is NOT saved in the player's profile.
	*/
	inline score getCurrentScore(holeID i){return validHole(i)? currentScores[i]:NO_SCORE;}
	/* 
	* Return the player's best ever score for the hole.
	* This score is loaded with the player's profile.
	* Since it is generally assumed that you can't clear a hole in zero or fewer shots,
	* a score of zero or less is treated as if the player has never cleared that hole before.
	*/
	inline score getHighScore(holeID i){return validHole(i)? highScores[i]:NO_SCORE;}
	// Sets the current score for the hole.
	inline void setCurrentScore(holeID i, score s){if (validHole(i)) currentScores[i] = s;}
	// Sets the high score for the hole, ignoring the previous value.
	inline void setHighScore(holeID i, score s){if (validHole(i)) highScores[i] = s;}
	/* Registers a score for the given hole. 
	* The current score will always be overwritten, as will the high score if the player has never
	* cleared the hole before or if their current score is better than their previous best.
	*/
	inline void registerScore(holeID i, score s){
		setCurrentScore(i,s);
		setHighScore(i, std::min(s, highScores[i]>NO_SCORE? highScores[i]:s));
	}
	/* Loads a profile from a text file.
	* Format for the text file is as follows:
	* Line 1: Number n of scores recorded.
	* All lines after: Score for hole 0-n.
	*/
	void loadProfile(char*);
	//Saves the player's profile using the same format as loadProfile().
	void saveProfile(char*);
	//Initializes the score arrays to take in a given number of holes.
	void loadHoles(holeID);
	//Returns the total current score of the round.
	score getTotalScore(holeID i);
	//Returns the total high score of the round.
	score getTotalHighScore(holeID i);
	//Returns the hole with the player's best score.
	holeID getBestHole();
	//Returns the hole with the player's best current score.
	holeID getCurrentBestHole();
	//Returns the hole with the player's worst score.
	holeID getWorstHole();
	//Returns the hole with the player's worst current score.
	holeID getCurrentWorstHole();
	//Scores below this value are considered unfinished holes.
	static const int NO_SCORE = 0;
protected:
	//The par of each course.
	ScoreContainer pars;
	//The current score of each course.
	ScoreContainer currentScores;
	//The high score of each course.
	ScoreContainer highScores;
	//The ID of the first hole.
	holeID firstHole;
	//The ID of the last hole.
	holeID lastHole;
	//The default filename to save to.
	char* profileName;
};

#endif

