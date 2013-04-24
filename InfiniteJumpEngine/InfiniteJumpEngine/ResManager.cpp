
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
			string type, id_str, num_str;
			iss >> type;
			if ( !type.compare( "tile" ) ) {
				int id;
				iss >> id_str;
				id = atoi(id_str.c_str( ));
				iss >> num_str;
				int numVerts = atoi(num_str.c_str( ));
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
				string n_str;
				for ( int n = 0; n < numVerts; n++ ) {
					iss >> n_str;
					neighbors.push_back( atoi(n_str.c_str( )) );
				}
				tiles->addTile( new Tile( id, verts, neighbors, glm::vec3( 0, 0.7, 0 ) ) );
			} else if ( !type.compare( "tee" ) ) {
				Entity * teeEntity = new Entity( );
				Mesh * tee = new Mesh( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
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
			} else if ( !type.compare( "cup" ) ) {
				Entity * cupEntity = new Entity( );
				Mesh * cup = new Mesh( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
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
				cup->addVert( x, y, z, 0, 1, 0, 0.5, 0.5, 0.5 ); 
				cup->addVert( x+0.5, y, z, 0, 1, 0, 0.5, 0.5, 0.5 ); 
				cup->addVert( x+0.5, y, z-0.5, 0, 1, 0, 0.5, 0.5, 0.5 );

				cup->addVert( x, y, z, 0, 1, 0, 0.5, 0.5, 0.5 ); 
				cup->addVert( x+0.5, y, z-0.5, 0, 1, 0, 0.5, 0.5, 0.5 );
				cup->addVert( x, y, z-0.5, 0, 1, 0, 0.5, 0.5, 0.5 );  
				cupEntity->addComponent( cup );
				level->addEntity( cupEntity );
			} else if ( !type.empty( ) ){
				cerr << "Found a unknown class type in " << filename << endl;
				return NULL;
			}

		}
		return level;
	} 

	return NULL;
}
