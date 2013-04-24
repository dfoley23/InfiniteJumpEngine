#include "Tile.h"
#include "Mesh.h"

Tile::Tile ( int nId, vector<glm::vec3> nVerts, vector<int> nEdges, glm::vec3 color ) {
	id = nId;
	this->color = color;
	for (unsigned int v = 0; v < nVerts.size(); v++){
		verts.push_back( nVerts[v] );
		if (v < nEdges.size()){
			neighbors.push_back ( nEdges[v] );
		} else {
			neighbors.push_back( NO_NEIGHBOR );
		}
	}
	mesh = generateMesh( );
}

Tile::~Tile ( ) {
	deleteMesh();
}

int Tile::findNeighbor(unsigned int nid){
	for (unsigned int e = 0; e < neighbors.size(); e++){
		if (neighbors[e] == nid)
			return e;
	}
	return NO_NEIGHBOR;
}

int Tile::getNeighbor(unsigned int e){
	if (e > 0 && e < neighbors.size())
		return neighbors[e];
	return NO_NEIGHBOR;
}

void Tile::deleteMesh(){
	if (mesh){
		delete mesh; mesh = NULL;
	}
}

Mesh* Tile::getMesh(){
	if (!mesh){ mesh = generateMesh();}
	return mesh;
}

Mesh* Tile::generateMesh(){
	Mesh * out = new Mesh( );
	glm::vec3 vert0;
	glm::vec3 vert1;
	glm::vec3 vert2;
	glm::vec3 norm;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	for (int v = 0; v < verts.size()-1; v++){
		if ( v < 2 ) {
			vert0 = verts[v];
			vert1 = verts[v+1];
			vert2 = verts[v+2];
			v++;
		} else {
			vert1 = verts[v];
			vert2 = verts[v+1];
		}
		tangent = vert1 - vert0;
		bitangent = vert2 - vert0;
		norm = glm::cross( tangent, bitangent );
		out->addVert(vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, color.x, color.y, color.z );
		out->addVert(vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, color.x, color.y, color.z );
		out->addVert(vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, color.x, color.y, color.z );
	}
	out->setShader( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
	return out;
}