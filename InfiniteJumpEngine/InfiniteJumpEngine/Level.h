

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
		FILE *fp;
		char *content = NULL;

		int count=0;

		if (!file.empty( )) {
			fp = fopen(file.data( ),"rt");

			if (fp != NULL) {

				fseek(fp, 0, SEEK_END);
				count = ftell(fp);
				rewind(fp);

				if (count > 0) {
					content = (char *)malloc(sizeof(char) * (count+1));
					count = fread(content,sizeof(char),count,fp);
					content[count] = '\0';
				}
				fclose(fp);
			}
		}
		delete [] content;
	}

	void loadLevel ( int i ) {
		if ( i == 0 ) {
			meshBatch = new MeshBatch( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
		}
	}

private:



};

#endif LEVEL_H
