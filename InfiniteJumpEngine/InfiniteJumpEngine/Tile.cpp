#include "Tile.h"

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
	verts.clear();
	neighbors.clear();
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

glm::vec3 Tile::getNormal(){
	return normal;
}

int Tile::getNeighbor(unsigned int e){
	if (e > 0 && e < neighbors.size())
		return neighbors[e];
	return NO_NEIGHBOR;
}

int Tile::getNeighborCount() {
	return static_cast<int>(neighbors.size());
}

int Tile::getTileId( ) {
	return id;
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

vector<PlaneCollider*> Tile::getEdgeColliders(){
	return edgeColliders;
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
		if ( v == 0 ) {
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
		this->normal = norm;
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
			vert2.x = vert1.x;
			vert2.y = vert1.y + edgeHeight*2;
			vert2.z = vert1.z;

			vert3.x = vert0.x;
			vert3.y = vert0.y + edgeHeight*2;
			vert3.z = vert0.z;
			
			/*tangent = vert1 - vert0;
			bitangent = vert2 - vert0;
			norm = glm::cross( tangent, bitangent );
			glm::vec3 eParralel = glm::normalize(glm::cross( norm, glm::vec3(0, 1, 0 ) ));
			glm::vec3 vec1 = (vert0 + vert1) / 2.f;
			glm::vec3 vec0 = vec1+norm;
			glm::vec3 vec2 = vec1+eParralel;
			
			glm::vec3 norm = glm::cross( vec1-vec0, vec2-vec0);
			glm::vec3 pointNorm = glm::cross( vec1-vec0, vert0-vec0 );
			if ( glm::dot( pointNorm, norm ) > 0 ) {
				vert0 = vert0 + eParralel * edgeHeight/2.0f;
				vert1 = vert1 - eParralel * edgeHeight/2.0f;
			} else {
				vert1 = vert0 + eParralel * edgeHeight/2.0f;
				vert0 = vert1 - eParralel * edgeHeight/2.0f;
			}*/
			edge->createYCube( edgeHeight/2.0f, edgeHeight, vert1, vert0, wall_color );
			edges.push_back( edge );

			//vert0.y = vert0.y - edgeHeight*5;
			//vert1.y = vert0.y - edgeHeight*5;
			PlaneCollider * pCollide = new PlaneCollider ( vert1, vert0, vert3, vert2, true );
			pCollide->setParent( this );
			edgeColliders.push_back( pCollide );

		} else {
			vert0 = verts[e];
			if (e < static_cast<int>(neighbors.size())-1){
				vert1 = verts[e+1];
			} else {
				vert1 = verts[0];
			}
			vert2.x = vert1.x;
			vert2.y = vert1.y + edgeHeight*2;
			vert2.z = vert1.z;
			
			vert3.x = vert0.x;
			vert3.y = vert0.y + edgeHeight*2;
			vert3.z = vert0.z;

			//vert0.y = vert0.y - edgeHeight*5;
			//vert1.y = vert0.y - edgeHeight*5;
			//PlaneCollider * pCollide = new PlaneCollider ( vert0, vert3, vert2, vert1, false );
			PlaneCollider * pCollide = new PlaneCollider ( vert0, vert1, vert2, vert3, false );
			pCollide->setParent( this );
			edgeColliders.push_back( pCollide );
		}
	}
	return out;
}