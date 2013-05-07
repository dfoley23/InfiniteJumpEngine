#include "Level.h"

// Constructors/Destructors
//  

Level::Level ( ) {
	camera = new Camera( ); 
	meshBatch = new MeshBatch( new Shader( "shaders/pointLight.vert", "shaders/pointLight.frag") );
	pickBatch = new MeshBatch( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
}

Level::~Level ( ) { 
	clear();
}

//  
// Methods
//  
void Level::update(float dT){
	camera->update( dT );
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->update( dT );
	}
}

void Level::draw( ){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->draw( meshBatch );
	}
	meshBatch->cam = camera->cam;
	meshBatch->proj = camera->proj;
	meshBatch->lightPos = camera->lightPos;
	meshBatch->draw( );
}

void Level::drawForPick( ){
	glm::vec3 pickColors = glm::vec3( 1, 0, 0 );
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->drawForPick( pickBatch, pickColors );
		pickColors.x+=5;
		if ( pickColors.x > 255 ) {
			pickColors.x = 0; 
			pickColors.y+=5;
			if ( pickColors.y > 255 ) {
				pickColors.y = 0;
				pickColors.z+=5;
			}
		}
	}
	pickBatch->cam = camera->cam;
	pickBatch->proj = camera->proj;
	pickBatch->lightPos = camera->lightPos;
	pickBatch->draw( );
}

vector<Entity *> Level::getEntities( ) {
	return entities;
}

void Level::clear( ){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		delete (*it);
	}
}

void Level::addEntity( Entity * entity ){
	entities.push_back(entity);
}

// Accessor methods
//  


// Other methods
//  