#include "Tile.h"
#include "Mesh.h"

Tile::Tile ( int nId, vector<glm::vec3> nVerts, vector<int> nEdges ) {
	id = nId;
	mesh = NULL;
	for (unsigned int v = 0; v < nVerts.size(); v++){
		verts[v] = nVerts[v];
		if (v < nEdges.size()){
			neighbors[v] = nEdges[v];
		} else {
			neighbors[v] = NO_NEIGHBOR;
		}
	}
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
	Mesh *out = new Mesh();
	glm::vec3 vert;
	for (int v = 0; v < verts.size(); v++){
		vert = verts[v];
		//out.addVert(vert.x, vert.y, vert.z);
	}
	return out;
}