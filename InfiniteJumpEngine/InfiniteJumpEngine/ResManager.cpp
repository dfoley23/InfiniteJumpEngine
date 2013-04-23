
#include "ResManager.h"

ResManager::ResManager(void)
{
}


ResManager::~ResManager(void)
{
}

Level* ResManager::getTriangleLevel(string filename){
	Level* level = new Level();
	Entity* terrain = new Entity();
	TileSet* tiles = new TileSet();
	terrain->addComponent(tiles);
	level->addEntity(terrain);

	string line;
	ifstream input;
	input.open(filename.c_str( ));

	if ( input.fail( ) ) {
		cerr << "Unable to open level file " << filename << endl;
	} else {
		for( int lineNum=0; !input.eof( ); lineNum++ ) {
			getline( input, line );
			istringstream iss(line);
			string sub;
			iss >> sub;
			if ( strcmp( sub.c_str( ), "tile" ) ) {
				int id;
				iss >> sub;
				id = atoi(sub.c_str( ));
				iss >> sub;
				int numVerts = atoi(sub.c_str( ));
				vector<glm::vec3> verts;
				glm::vec3 vertex;
				string str_x, str_y, str_z;
				for( int v = 0; v < numVerts; v++ ) { 
					iss >> str_x;
					iss >> str_y;
					iss >> str_z;
					vertex = glm::vec3( atof(str_x.c_str( )), 
						atof(str_y.c_str( )), atof(str_z.c_str( )));
					verts.push_back(vertex);
				}
				vector<int> neighbors;
				for ( int n = 0; n < numVerts; n++ ) {
					iss >> sub;
					neighbors.push_back( atoi(sub.c_str( )) );
				}
				//TODO add tile to tileset
			} else if ( strcmp( sub.c_str( ), "tee" ) ) {
				Entity * teeEntity = new Entity( );
				Mesh * tee = new Mesh( );
				string str_id;
				string str_x, str_y, str_z;
				iss >> str_id;
				int i = atoi(str_id.c_str( ));
				iss >> str_x;
				iss >> str_y;
				iss >> str_z;
				float x = atof( str_x.c_str( ) );
				float y = atof( str_y.c_str( ) );
				float z = atof( str_z.c_str( ) );
				//tee mesh
				tee->addVert( x, y, z, 0, 1, 0, 0, 0, 1 ); 
				tee->addVert( x+0.1, y, z, 0, 1, 0, 0, 0, 1 ); 
				tee->addVert( x+0.1, y, z-0.1, 0, 1, 0, 0, 0, 1 );

				tee->addVert( x, y, z, 0, 1, 0, 0, 0, 1 ); 
				tee->addVert( x+0.1, y, z-0.1, 0, 1, 0, 0, 0, 1 );
				tee->addVert( x, y, z-0.1, 0, 1, 0, 0, 0, 1 ); 
				teeEntity->addComponent( tee );
				level->addEntity( teeEntity );
			} else if ( strcmp( sub.c_str( ), "cup" ) ) {
				Entity * cupEntity = new Entity( );
				Mesh * cup = new Mesh( );
				string str_id;
				string str_x, str_y, str_z;
				iss >> str_id;
				int i = atoi(str_id.c_str( ));
				iss >> str_x;
				iss >> str_y;
				iss >> str_z;
				float x = atof( str_x.c_str( ) );
				float y = atof( str_y.c_str( ) );
				float z = atof( str_z.c_str( ) );
				//cup mesh
				cup->addVert( x, y, z, 0, 1, 0, 0, 0, 1 ); 
				cup->addVert( x+0.1, y, z, 0, 1, 0, 0, 0, 1 ); 
				cup->addVert( x+0.1, y, z-0.1, 0, 1, 0, 0, 0, 1 );

				cup->addVert( x, y, z, 0, 1, 0, 0, 0, 1 ); 
				cup->addVert( x+0.1, y, z-0.1, 0, 1, 0, 0, 0, 1 );
				cup->addVert( x, y, z-0.1, 0, 1, 0, 0, 0, 1 );  
				cupEntity->addComponent( cup );
				level->addEntity( cupEntity );
			} else {
				cerr << "Found a unknown class type in " << filename << endl;
				return NULL;
			}

		}
		return level;
	} 

	return NULL;
}
