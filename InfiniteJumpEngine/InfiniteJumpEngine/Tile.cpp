#include "Tile.h"
#include "Mesh.h"

Tile::Tile ( int nId, vector<glm::vec3> nVerts, vector<int> nEdges, glm::vec3 color ) {
	id = nId;
	this->color = color;
	wall_color.r = 0.5f;
	wall_color.g = 0.25f;
	wall_color.b = 0.0f;
	for (unsigned int v = 0; v < static_cast<int>(nVerts.size()); v++){
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

void Tile::draw( MeshBatch * batch ) {
	getMesh()->draw(batch);
	for ( int i=0; i<static_cast<int>(edges.size()); i++ ) {
		edges.at(i)->draw( batch );
	}
}

void Tile::drawForPick( MeshBatch * batch, glm::vec3 pickColors ) {
	getMesh()->drawForPick(batch, pickColors);
	for ( int i=0; i<static_cast<int>(edges.size()); i++ ) {
		edges.at(i)->drawForPick( batch, pickColors );
	}
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
	glm::vec3 vert3;
	glm::vec3 norm;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	float edgeHeight = 0.1f;
	for (int v = 0; v < static_cast<int>(verts.size())-1; v++){
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
	for (int e = 0; e < static_cast<int>(neighbors.size()); e++){
		if (neighbors.at(e) == Tile::NO_NEIGHBOR){
			Mesh * edge = new Mesh( );
			vert0 = verts[e];
			if (e < static_cast<int>(neighbors.size())-1){
				vert1 = verts[e+1];
			} else {
				vert1 = verts[0];
			}
			vert2.x = vert0.x;
			vert2.y = vert0.y + edgeHeight;
			vert2.z = vert0.z;

			vert3.x = vert1.x;
			vert3.y = vert1.y + edgeHeight;
			vert3.z = vert1.z;

			tangent = vert2 - vert1;
			bitangent = vert3 - vert1;
			norm = glm::cross( tangent, bitangent );

			edge->createYCube( edgeHeight/2.0f, edgeHeight, vert0, vert1, wall_color );
			edges.push_back( edge );
			/*
			// facing the tile
			//Face 1: 0 -> 1 -> 2
			out->addVert(vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, wall_color.x, wall_color.y, wall_color.z );
			out->addVert(vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, wall_color.x, wall_color.y, wall_color.z );
			out->addVert(vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, wall_color.x, wall_color.y, wall_color.z );
			//Face 2: 1 -> 2 -> 3
			out->addVert(vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, wall_color.x, wall_color.y, wall_color.z );
			out->addVert(vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, wall_color.x, wall_color.y, wall_color.z );
			out->addVert(vert3.x, vert3.y, vert3.z, norm.x, norm.y, norm.z, wall_color.x, wall_color.y, wall_color.z );*/

		}
	}
	return out;
}