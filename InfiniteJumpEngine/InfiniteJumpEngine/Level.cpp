#include "Level.h"

// Constructors/Destructors
//  

Level::Level ( string name ) {
	camera = new Camera( ); 
	hudView = new MatrixComponent( );
	//set the hud ortho transformation
	glm::mat4 hudMat = glm::ortho( -1.f, 1.f, -1.f, 1.f );
	hudView->setMatrix( hudMat );
	//make a mesh batch for the world elements
	meshBatch = new MeshBatch( new Shader( "shaders/pointLight.vert", "shaders/pointLight.frag") );
	//make a mesh batch for all of the hud elements
	hudBatch = new MeshBatch( new Shader( "shaders/spriteBasic.vert", "shaders/spriteBasic.frag") );
	hudBatch->texName = "hudAtlas";
	hudElement1 = NULL;
	ball = NULL;
	orientation = 0.0f;
}

Level::~Level ( ) { 
	clear();
	vector<Entity*>().swap(entities);
	delete meshBatch;
	delete hudBatch;
}

//  
// Methods
//  
/*
* updates all of the entities in the level
*/
void Level::update(float dT){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->update( dT );
	}
		

	//TODO this stuff should go into the compass update script
	//hud stuff
	glm::vec3 dir = camera->getDir();
	dir.y = 0;
	float dDotNorth = glm::dot( glm::normalize(dir), glm::vec3( 0, 0, -1 ) );
	float theta = glm::acos( dDotNorth);
	orientation = theta * rad_to_deg;
	if ( dir.x < 0 ) {
		orientation = -orientation;
	}
	//rotate the compass
	if ( hudElement1  != NULL ) 
		hudElement1->rotate( orientation, glm::vec3( 0, 0, 1 ) );
}

void Level::draw( ){
	//draw the world
	glEnable( GL_DEPTH_TEST );
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->draw( meshBatch );
	}
	meshBatch->cam = camera->cam;
	meshBatch->proj = camera->proj;
	meshBatch->lightPos = camera->lightPos;
	meshBatch->draw( );

	//draw the hud with depth disabled and blending enabled
	glDisable( GL_DEPTH_TEST );
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for(entityIter it = hudEntities.begin(); it != hudEntities.end(); ++it) {
		(*it)->draw( hudBatch );
	}
	hudBatch->cam = hudView->getTransformation();
	hudBatch->proj = glm::mat4( 1.0f );
	hudBatch->lightPos = glm::vec3( 0, 0, 1 );
	hudBatch->draw( );
	glDisable( GL_BLEND );
}

void Level::drawForPick( ){

}

vector<Entity *> Level::getEntities( ) {
	return entities;
}

void Level::clear( ){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		delete (*it);
	}
	entities.clear();
}

void Level::addEntity( Entity * entity ){
	entities.push_back(entity);
}

// Accessor methods
//  


// Other methods
//  