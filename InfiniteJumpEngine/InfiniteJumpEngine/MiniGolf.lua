registryTable = { }

function registerObject( key, value ) 
	registryTable[key] = value
end

function printTable( )
	print (registryTable)
end

function getRegisteredObject( key )
	return registryTable[ key ]
end

function loadDefaultScene( argc )
	print ("Arguments received:" + argc + "\n")
	--[[	
	--Define Camera
	camera = Camera.init()
	
	--Define Course
	hole = 0
	filename = "courses.db"
	if argc > 1 then 
		filename = argv[2]
		if argc > 2 then
			hole = argv[3] 
		end
	end
	course = GolfHoleSelector.__init(filename)
	course.setCurrentHole(hole)
	
	--Define HUD
	hudRoot = GolfHud.init()
	hudGLUI = GLUIComponent.init()
	compass = Compass.init()
	hudRoot.addComponent(compass)
	hudRoot.addComponent(hudGLUI)
	
	root.addComponent(course)
	root.addComponent(hudRoot)
	]]--
end

--[[C++ Version of the Golf Loading algorithm
Level* ResManager::getTriangleLevel(string filename, int holeID){
	Level* level = new Level( "golfLevel" );
	level->maxSubLevels = 0;
	Ball * ball = NULL;
	Cup * cup = NULL;
	vector<PlaneCollider*> tileColliders;
	bool end_hole = false;
	bool begin_hole = false;
	bool course = false;
	int skip = 0;
	if ( holeID < 0 ) {
		//builds the main menu
		Entity * hudEntity = new Entity( );
		Mesh * hudMesh = new Mesh( );
		glm::vec3 vert0 = glm::vec3( -0.25, -0.25, 0 );
		glm::vec3 vert1 = glm::vec3( 0.25, -0.25, 0 );
		glm::vec3 vert2 = glm::vec3( 0.25, 0.25, 0 );
		glm::vec3 vert3 = glm::vec3( -0.25, 0.25, 0 );
		glm::vec3 norm = glm::vec3( 0, 0, 1 );
		hudMesh->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1, 0, 1 );
		hudMesh->addVert( vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, 1, 1, 1, 1, 1 );
		hudMesh->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1, 1, 0 );
		hudMesh->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1, 0, 1 );
		hudMesh->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1, 1, 0.0 );
		hudMesh->addVert( vert3.x, vert3.y, vert3.z, norm.x, norm.y, norm.z, 1, 1, 1, 0, 0 );
		hudEntity->addComponent( hudMesh );
		level->hudEntities.push_back( hudEntity );
		loadTextureList( "MainMenu" );
		return level;
	} else {
		loadTextureList( "golfLevel" );
	}
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
		while( !end_hole ) {
			getline( input, line );
			if ( input.eof( ) ) {
				break;
			}
			istringstream iss(line);
			string type, id_str, num_str;
			iss >> type;
			if ( !type.compare( "tile" ) ) {
				if ( !course || begin_hole ) {
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
					tiles->addTile( id, new Tile( id, verts, neighbors, glm::vec3( 0.0f, 0.7f , 0.0f ) ) );
					//tiles->addTile( id, new Tile( id, verts, neighbors, glm::vec3( (float)id/17.f, (float)id/17.f, (float)id/17.f) ) );
					//tiles->addTile( id, new Tile( id, verts, neighbors, glm::vec3( 0.5, 0.5, 0.5 + id/34.f ) ) );
				}
			} else if ( !type.compare( "tee" ) ) {
				if ( !course || begin_hole ) {
					Entity * teeEntity = new Entity( );
					Mesh * tee = new Mesh( );
					string str_id;
					string str_x, str_y, str_z;
					iss >> str_id;
					int id = atoi(str_id.c_str( ));
					iss >> str_x;
					iss >> str_y;
					iss >> str_z;
					float x = static_cast<float>(atof( str_x.c_str( ) ));
					float y = static_cast<float>(atof( str_y.c_str( ) ));
					float z = static_cast<float>(atof( str_z.c_str( ) ));
					//tee mesh

					glm::vec3 vert0 = glm::vec3( x-0.05f, y+0.001f, z+0.05f );
					glm::vec3 vert1 = glm::vec3( x+0.05f, y+0.001f, z+0.05f );
					glm::vec3 vert2 = glm::vec3( x+0.05f, y+0.001f, z-0.05f );
					glm::vec3 vert3 = glm::vec3( x-0.05f, y+0.001f, z-0.05f );

					glm::vec3 tangent = vert1 - vert0;
					glm::vec3 bitangent = vert2 - vert0;
					glm::vec3 norm = glm::cross( tangent, bitangent );

					tee->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1 );

					tee->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert3.x, vert3.y, vert3.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					//tee->createYCube( 0.1f, 0.005f, vert0, vert1, color );

					teeEntity->addComponent( tee );
					level->addEntity( teeEntity );

					//build ball on tee
					Entity * ballEntity = new Entity();
					ball = new Ball( glm::vec3(x, y, z), glm::vec3( 1, 1, 1), tiles, id );
					ballEntity->addComponent( ball );
					level->addEntity( ballEntity );
					level->pickedMesh = ball->getMesh( );
					level->ball = ball;
				}
			} else if ( !type.compare( "cup" ) ) {
				if ( !course || begin_hole ) {
					Entity * cupEntity = new Entity( );
					string str_id;
					string str_x, str_y, str_z;
					iss >> str_id;
					iss >> str_x;
					iss >> str_y;
					iss >> str_z;
					float x = static_cast<float>(atof( str_x.c_str( ) ));
					float y = static_cast<float>(atof( str_y.c_str( ) ));
					float z = static_cast<float>(atof( str_z.c_str( ) ));
					cup = new Cup( glm::vec3( x, y+0.001, z) );

					cupEntity->addComponent( cup );
					level->addEntity( cupEntity );

				}
			} else if ( !type.compare( "course" ) ) {
				course = true;
				string course_name, numHoles_str;
				iss >> course_name;
				iss >> numHoles_str;
				int numHoles = atoi( numHoles_str.c_str() ) - 1;
				level->maxSubLevels = numHoles;
				Game::game()->scores.loadHoles(numHoles+1);
				Game::game()->holeName->set_text(course_name.c_str());
			} else if ( !type.compare( "begin_hole" ) ) {
				if ( skip == holeID ) {
					begin_hole = true;
				} else {
					skip++;
				}
			} else if ( !type.compare( "name" ) ) { 
				string hole_name = "";
				string name_append;
				bool read = true;
				while ( read ) { 
					read = iss >> name_append;
					if ( read ) {
						hole_name = hole_name + " " + name_append;
					}
				}
				string hole_num;
				stringstream out;
				int holeNum = skip + 1;
				out << holeNum;
				hole_num = out.str();
				string complete = "hole " + hole_num + ": " + hole_name;
				Game::game()->holeName->set_text(complete.c_str());
			} else if ( !type.compare( "par" ) ) {
				string par_num;
				iss >> par_num;
				string complete = "Par " + par_num;
				Game::game()->holePar->set_text(complete.c_str());
				Game::game()->totalPar += atoi( par_num.c_str() );
				Game::game()->curPar = atoi( par_num.c_str() );
				Game::game()->holeStrokeCount = 0;
				int score = 0 - atoi(par_num.c_str());
				string score_str;
				stringstream out;
				out << score;
				score_str = out.str();
				Game::game()->holeScore->set_text(score_str.c_str());
			} else if ( !type.compare( "end_hole" ) ) {
				if ( begin_hole ) 
					end_hole = true;
			} else if ( !type.empty( ) ){
				cerr << "Found a unknown class type in " << filename << endl;
				//return NULL;
			}
		}
		if ( ball ) {
			ball->cup = cup;
		}
		//insert all the colliders for the tiles
		vector<PlaneCollider*> colliders = cup->edgeColliders;
		for( int i=0; i<static_cast<int>(colliders.size()); i++ ) {
			ball->getPhysics()->addCollider(colliders.at(i));
		}
		//add all hud entities
		Entity * hudEntity = new Entity( );
		Mesh * hudMesh = new Mesh( );
		glm::vec3 vert0 = glm::vec3( -0.16, -0.25, 0 );
		glm::vec3 vert1 = glm::vec3( 0.16, -0.25, 0 );
		glm::vec3 vert2 = glm::vec3( 0.16, 0.25, 0 );
		glm::vec3 vert3 = glm::vec3( -0.16, 0.25, 0 );
		glm::vec3 norm = glm::vec3( 0, 0, 1 );
		hudMesh->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1, 0, 1 );
		hudMesh->addVert( vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, 1, 1, 1, 0.5, 1 );
		hudMesh->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1, 0.5, 0 );
		hudMesh->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1, 0, 1 );
		hudMesh->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1, 0.5, 0.0 );
		hudMesh->addVert( vert3.x, vert3.y, vert3.z, norm.x, norm.y, norm.z, 1, 1, 1, 0, 0 );
		hudEntity->addComponent( hudMesh );
		hudMesh->translate( 0.77f, -0.70f, 0 );
		level->hudElement1 = hudMesh;
		level->hudEntities.push_back( hudEntity );

		hudEntity = new Entity( );
		hudMesh = new Mesh( );
		vert0 = glm::vec3( -0.01, -0.01, 0 );
		vert1 = glm::vec3( 0.01, -0.01, 0 );
		vert2 = glm::vec3( 0.01, 0.01, 0 );
		vert3 = glm::vec3( -0.01, 0.01, 0 );
		norm = glm::vec3( 0, 0, 1 );
		hudMesh->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 0, 0.5f, 0.5f );
		hudMesh->addVert( vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, 1, 1, 0, 0.63f, 0.5f );
		hudMesh->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 0, 0.63f, 0.0f );
		hudMesh->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 0, 0.5f, 0.5f );
		hudMesh->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 0, 0.63f, 0.0f );
		hudMesh->addVert( vert3.x, vert3.y, vert3.z, norm.x, norm.y, norm.z, 1, 1, 0, 0.5f, 0.0f );
		hudEntity->addComponent( hudMesh );
		level->ballDirHud = hudMesh;
		level->hudEntities.push_back( hudEntity );
		return level;
	} 
	return NULL;
}
]]--