

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

#include "Entity.h"
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

	Level ( string filename ) { loadLevel( filename ); };
	Level ( int i ) { loadLevel( i ); };
public:
	
	vector<Entity*> entities;
	MeshBatch * meshBatch;

	void draw( ) {
		for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
			(*it)->draw( meshBatch );
		}
		meshBatch->draw( );
	}

	void loadLevel(string file )
	{
		//read source code
		ifstream fin(file.c_str());
		if (fin.fail()) {
			cerr << "Could not open " << file << " for reading" << endl;
		} else {
			fin.seekg(0, ios::end);
			int count  = fin.tellg();
			char *data = NULL;
			if (count > 0) {
				fin.seekg(ios::beg);
				data = new char[count+1];
				fin.read(data,count);
				data[count] = '\0';
			}
			fin.close();

			delete [] data;
		}
	}

	void loadLevel ( int i ) {
		if ( i == 0 ) {
			meshBatch = new MeshBatch( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
		}
	}

private:



};

#endif LEVEL_H
