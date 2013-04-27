
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
					vertex = glm::vec3( static_cast<float>(atof(str_x.c_str( ))), 
						static_cast<float>(atof(str_y.c_str( ))),
						static_cast<float>(atof(str_z.c_str( ))));
					verts.push_back(vertex);
				}
				vector<int> neighbors;
				string n_str;
				for ( int n = 0; n < numVerts; n++ ) {
					iss >> n_str;
					neighbors.push_back( atoi(n_str.c_str( )) );
				}
				tiles->addTile( new Tile( id, verts, neighbors, glm::vec3( 0, 0.7f, 0 ) ) );
			} else if ( !type.compare( "tee" ) ) {
				Entity * teeEntity = new Entity( );
				Mesh * tee = new Mesh( new Shader( "shaders/pointLight.vert", "shaders/pointLight.frag") );
				string str_id;
				string str_x, str_y, str_z;
				iss >> str_id;
				int i = atoi(str_id.c_str( ));
				iss >> str_x;
				iss >> str_y;
				iss >> str_z;
				float x = static_cast<float>(atof( str_x.c_str( ) ));
				float y = static_cast<float>(atof( str_y.c_str( ) ));
				float z = static_cast<float>(atof( str_z.c_str( ) ));
				//tee mesh
				glm::vec3 vert0 = glm::vec3( x, y, z );
				glm::vec3 vert1 = glm::vec3( x, y, z+0.1f );
				glm::vec3 color = glm::vec3( 1, 1, 1 );
				tee->createYCube( 0.1f, 0.005f, vert0, vert1, color );

				teeEntity->addComponent( tee );
				level->addEntity( teeEntity );
			} else if ( !type.compare( "cup" ) ) {
				Entity * cupEntity = new Entity( );
				Mesh * cup = new Mesh( new Shader( "shaders/pointLight.vert", "shaders/pointLight.frag") );
				string str_id;
				string str_x, str_y, str_z;
				iss >> str_id;
				int i = atoi(str_id.c_str( ));
				iss >> str_x;
				iss >> str_y;
				iss >> str_z;
				float x = static_cast<float>(atof( str_x.c_str( ) ));
				float y = static_cast<float>(atof( str_y.c_str( ) ));
				float z = static_cast<float>(atof( str_z.c_str( ) ));
				//cup mesh
				glm::vec3 vert0 = glm::vec3( x+0.15f, y, z+0.15f );
				glm::vec3 vert1 = glm::vec3( x+0.15f, y, z-0.15f );
				glm::vec3 color = glm::vec3( 0, 0, 0 );
				cup->createYCube( 0.3f, 0.002f, vert0, vert1, color );

				cupEntity->addComponent( cup );
				level->addEntity( cupEntity );
				level->cupMeshToMove = cup;
			} else if ( !type.empty( ) ){
				cerr << "Found a unknown class type in " << filename << endl;
				return NULL;
			}

		}
		return level;
	} 

	return NULL;
}
