#include "Tile.h"
#include "Mesh.h"

// Constants
const int Tile::GROUND_VERTS = 4;

// Constructors/Destructors
//  

Tile::Tile ( ) {
	initAttributes();
	//Initialize array of ground vertices

	groundVerts = new float*[GROUND_VERTS];
	for (int i = 0; i < GROUND_VERTS; ++i)
		groundVerts[i] = new float[Mesh::VERT_SIZE];
}

Tile::~Tile ( ) {
}

vector<float>* getVerts(){
	vector<float> *verts = new vector<float>();

	return verts;
}

// Other methods
//  

void Tile::initAttributes ( ) {
}

