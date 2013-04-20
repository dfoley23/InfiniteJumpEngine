

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
		loadLevel( filename ); 
		camera = new Camera( ); 
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
