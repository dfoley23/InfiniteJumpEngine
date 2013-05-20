#include "Cup.h"

Cup::Cup ( glm::vec3 pos ) {
	this->pos = pos;
	mesh = generateMesh( );
	mesh->translate( pos.x, pos.y, pos.z );
	glm::vec3 vert0;
	glm::vec3 vert1;
	glm::vec3 vert2;
	glm::vec3 vert3;
	float planeHeight = 0.3f;
	Mesh * tempCollisionMesh = Game::game()->resman->readObjFile( "cupCollide.obj" );
	vector<float> verts = tempCollisionMesh->getVerts();
	for( int i=0 ; i< static_cast<int>(verts.size())-11; i++ ) {
		vert0 = glm::vec3( verts.at(i)+pos.x, verts.at(i+1)+pos.y, verts.at(i+2)+pos.z );
		vert1 = glm::vec3( verts.at(i+3)+pos.x, verts.at(i+4)+pos.y, verts.at(i+5)+pos.z );
		vert2 = glm::vec3( verts.at(i+6)+pos.x, verts.at(i+7)+pos.y, verts.at(i+8)+pos.z );
		vert3 = glm::vec3( verts.at(i+9)+pos.x, verts.at(i+10)+pos.y, verts.at(i+11)+pos.z );
			
		vert0.y -= planeHeight;
		vert1.y -= planeHeight;
		PlaneCollider * pCollide = new PlaneCollider ( vert1, vert0, vert3, vert2, false );
		pCollide->setParent( this );
		edgeColliders.push_back( pCollide );
		i+=11;
	}
	delete tempCollisionMesh;
	verts.clear();
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
	return Game::game()->resman->readObjFile( "cupMesh.obj" );
}

void Cup::receiveMessage( IJMessage* message ){
	if (!message->getContent().compare("InterSection")){
		sendMessage( message->getOther(), this, "CupCollide", message->getVector() );
	}
}