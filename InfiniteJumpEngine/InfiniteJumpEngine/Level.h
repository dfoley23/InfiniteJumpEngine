

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

#include "Entity.h"
#include "Camera.h"
using namespace std;
/**
* class Level
* 
*/

typedef std::vector<Entity*>::iterator entityIter;

class Level
{
public:

	// Constructors/Destructors
	//  


	/**
	* Empty Constructor
	*/
	Level ( );

	/**
	* Empty Destructor
	*/
	virtual ~Level ( );

	Camera * camera;
	vector<Entity*> entities;

	void update(float);

	void draw( );

	void clear( );

private:



};

#endif LEVEL_H
