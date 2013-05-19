#include "Cup.h"

Cup::Cup ( glm::vec3 pos ) {
	this->pos = pos;
	mesh = generateMesh( );
}

Cup::~Cup ( ) {
	verts.clear();
	deleteMesh();
}

void Cup::draw( MeshBatch * batch ) {
	getMesh()->draw(batch);
}

void Cup::drawForPick( MeshBatch * batch, glm::vec3 pickColors ) {
	getMesh()->drawForPick(batch, pickColors);
}

void Cup::deleteMesh(){
	if (mesh){
		delete mesh; mesh = NULL;
	}
}

Mesh* Cup::getMesh(){
	if (!mesh){ mesh = generateMesh();}
	return mesh;
}

Mesh* Cup::generateMesh(){
	return Game::game()->resman->readObjFile( "ballobj.obj" );
}

void Cup::receiveMessage( IJMessage* message ){
	if (!message->getContent().compare("BallCollide")){

	}
}