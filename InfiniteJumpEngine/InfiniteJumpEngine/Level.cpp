#include "Level.h"

// Constructors/Destructors
//  

Level::Level ( string name ) {
	camera = new Camera( ); 
	hudView = new MatrixComponent( );
	glm::mat4 hudMat = glm::ortho( -1.f, 1.f, 1.f, -1.f );
	hudView->setMatrix( hudMat );
	meshBatch = new MeshBatch( new Shader( "shaders/pointLight.vert", "shaders/pointLight.frag") );
	hudBatch = new MeshBatch( new Shader( "shaders/spriteBasic.vert", "shaders/spriteBasic.frag") );
	hudBatch->texName = "hudAtlas";
	pickBatch = new MeshBatch( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
	
	orientation = 0.0f;
}

Level::~Level ( ) { 
	clear();
	vector<Entity*>().swap(entities);
	delete meshBatch;
	delete pickBatch;
	delete hudBatch;
}

//  
// Methods
//  
void Level::update(float dT){
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->update( dT );
	}
		
	//hud stuff
	glm::vec3 dir = ball->getPhysics()->getKinematics()->vel.getPosition();
	glm::vec3 projDir = glm::vec3( dir.x, dir.z, 0 );
	if ( glm::length( projDir ) > 0 ) {
		orientation = glm::acos(glm::dot( projDir, glm::vec3( 0, 1, 0 ) ) );
	}
	hudElement1->rotate( orientation, glm::vec3( 0, 0, 1 ) );
}

void Level::draw( ){
	glEnable( GL_DEPTH_TEST );
	for(entityIter it = entities.begin(); it != entities.end(); ++it) {
		(*it)->draw( meshBatch );
	}
	meshBatch->cam = camera->cam;
	meshBatch->proj = camera->proj;
	meshBatch->lightPos = camera->lightPos;
	meshBatch->draw( );

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
	//for(entityIter it = entities.begin(); it != entities.end(); ++it) {
	//	delete (*it);
	//}
	entities.clear();
}

void Level::addEntity( Entity * entity ){
	entities.push_back(entity);
}

// Accessor methods
//  


// Other methods
//  