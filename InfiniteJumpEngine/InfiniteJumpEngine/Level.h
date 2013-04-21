

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

	Level ( string filename ) { 
		camera = new Camera( ); 
		loadLevel( filename ); 
	};
	Level ( int i ) { 
		camera = new Camera( ); 
		loadLevel( i ); 
	};

	Camera * camera;
	vector<Entity*> entities;

	void draw( ) {
		for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
			(*it)->draw( camera );
		}
	}

	void loadLevel(string file )
	{
		
	}

	void loadLevel ( int i ) {
	}

	void remove( ) {
		for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
			//(*it)->remove( );
			//delete (*it)->shader;
		}
	}

private:



};

#endif LEVEL_H
