#include "Mesh.h"

// Static Members
//
const int Mesh::VERT_SIZE = 3;
const int Mesh::UV_SIZE = 2;

// Constructors/Destructors
//  

Mesh::Mesh ( ) {
	initAttributes();
}

Mesh::~Mesh ( ) { }

/**
* @param  meshFile
*/
void Mesh::createMesh (string meshFile )
{
}


void Mesh::draw( MeshBatch * batch ) {
	glm::vec3 vert;
	glm::vec3 norm;
	glm::vec3 color;
	int index = 0;
	if ( dynamic ) {
		batch->verts.resize( batch->verts.size( ) + 1 );
		batch->norms.resize( batch->norms.size( ) + 1 );
		batch->colors.resize( batch->colors.size( ) + 1 );
		index = static_cast<int>(batch->verts.size( )) - 1;
		modelView = glm::mat4( );
		modelView = translations * rotations * scaling; 
		batch->modelViews.push_back( modelView );
	}
	for(int i=0; i < static_cast<int>(verts.size()); i++) {
		batch->verts.at(index).push_back( verts.at(i) );
		batch->norms.at(index).push_back( norms.at(i) );
		batch->colors.at(index).push_back( colors.at(i) );
	}
}

void Mesh::drawForPick( MeshBatch * batch, glm::vec3 pickColors ) {
	pickId.x = pickColors.x;
	pickId.y = pickColors.y;
	pickId.z = pickColors.z;
	int index = 0;
	if ( dynamic ) {
		batch->verts.resize( batch->verts.size( ) + 1 );
		batch->norms.resize( batch->norms.size( ) + 1 );
		batch->colors.resize( batch->colors.size( ) + 1 );
		index = static_cast<int>(batch->verts.size( )) - 1;
		modelView = glm::mat4( );
		modelView = translations * rotations * scaling; 
		batch->modelViews.push_back( modelView );
	}
	for(int i=0; i < static_cast<int>(verts.size()); i++) {
		batch->verts.at(index).push_back( verts.at(i) );
		batch->norms.at(index).push_back( norms.at(i) );
		if ( i % 3 == 0 ) {
			batch->colors.at(index).push_back( pickColors.x / 255.0f );
			batch->colors.at(index).push_back( pickColors.y / 255.0f );
			batch->colors.at(index).push_back( pickColors.z / 255.0f );
		}
	}
}

/**
* @param  x
* @param  y
* @param  z
*/
void Mesh::translate (float x, float y, float z )
{
	dynamic = true;
	translations = glm::mat4();
	translations = glm::translate( glm::mat4( ), glm::vec3( x, y, z ) );
}


/**
* @param  dir
* @param  up
*/
void Mesh::rotate (float angle, glm::vec3 axis)
{
	dynamic = true;
	rotations = glm::rotate( glm::mat4( ), angle, axis );
}

/**
*
*
*/
void Mesh::rotate( float x, float y, float z ) {
	dynamic = true;
	glm::mat4 rotateX = glm::rotate( glm::mat4( ), x, glm::vec3( 1, 0, 0 ) );
	glm::mat4 rotateY = glm::rotate( glm::mat4( ), y, glm::vec3( 0, 1, 0 ) );
	glm::mat4 rotateZ = glm::rotate( glm::mat4( ), z, glm::vec3( 0, 0, 1 ) );
	rotations = glm::mat4( );
	rotations = rotateX * rotateY * rotateZ;
}

/**
* @param  x
* @param  y
* @param  z
*/
void Mesh::scale (float x, float y, float z )
{
	dynamic = true;
	scaling = glm::scale( glm::mat4( ), glm::vec3( x, y, z ) );
}

void Mesh::setDynamic( bool setting ) {
	dynamic = setting;
}

void Mesh::remove ( ) {
	verts.erase( verts.begin( ), verts.end( ) );
	norms.erase( norms.begin( ), norms.end( ) );
	colors.erase( colors.begin( ), colors.end( ) );
	textureNames.erase( textureNames.begin( ), textureNames.end( ) );
}

void Mesh::addVert (float x, float y, float z, float r, float g, float b){
	float nx = 0, ny = 0, nz = 0;
	//Calculate normal from previous verts if possible
	addVert (x,y,z,nx,ny,nz, r, g, b);
}

void Mesh::addVert (float x, float y, float z, float nx, float ny, float nz, float r, float g, float b){
	if ( verts.empty( ) ) {
		min = glm::vec3 ( x, y, z );
		max = glm::vec3 ( x, y, z );
		center = glm::vec3( 0, 0, 0 );
	} else if ( x < min.x && y < min.y && z < min.z ) {
		min = glm::vec3( x, y, z );
	} else if ( x > max.x && y > max.y && z > max.z ) {
		max = glm::vec3 ( x, y, z );
	}
	center.x = (center.x + x) / static_cast<float>(verts.size());
	center.y = (center.y + y) / static_cast<float>(verts.size());
	center.z = (center.z + z) / static_cast<float>(verts.size());
	verts.push_back(x);
	verts.push_back(y);
	verts.push_back(z);
	norms.push_back(nx);
	norms.push_back(ny);
	norms.push_back(nz);
	colors.push_back(r);
	colors.push_back(g);
	colors.push_back(b);

}

void Mesh::createYCube( float depth, float height, 
	glm::vec3 vert0, glm::vec3 vert1, 
	glm::vec3 color ) {
		glm::vec3 vert2 = glm::vec3( vert1.x, vert1.y + height, vert1.z );
		glm::vec3 tangent = vert1 - vert0;
		glm::vec3 bitangent = vert2 - vert0;
		glm::vec3 norm = glm::normalize( glm::cross( tangent, bitangent ) );

		glm::vec3 perpDepth = glm::vec3 ( -norm.x * depth, 0, -norm.z * depth );
		glm::vec3 zeroDepth = glm::vec3 ( 0, 0, 0 );
		//top face
		createPlane( perpDepth, 0, vert0.x, vert0.y+height, vert0.z, vert2.x, vert2.y, vert2.z, color );
		//front face
		createPlane( zeroDepth, height, vert0.x, vert0.y, vert0.z, vert1.x, vert1.y, vert1.z, color );
		//back face
		createPlane( zeroDepth, height, vert1.x+perpDepth.x, vert1.y, vert1.z+perpDepth.z, 
			vert0.x+perpDepth.x, vert0.y, vert0.z+perpDepth.z, color );
		//left face
		createPlane( zeroDepth, height, vert0.x+perpDepth.x, vert0.y, vert0.z+perpDepth.z, vert0.x, vert0.y, vert0.z, color );
		//right face
		createPlane( zeroDepth, height, vert1.x, vert1.y, vert1.z, vert1.x+perpDepth.x, vert1.y, vert1.z+perpDepth.z, color );
		//bottom face
		createPlane( perpDepth, 0, vert1.x, vert1.y, vert1.z, vert0.x, vert0.y, vert0.z, color );
}

void Mesh::createPlane( glm::vec3 perpDepth, float height, float x1, float y1, float z1, float x2, float y2, float z2, glm::vec3 color ) {
	glm::vec3 vert0 = glm::vec3( x1, y1, z1 );
	glm::vec3 vert1 = glm::vec3( x2, y2, z2 );
	glm::vec3 vert2 = glm::vec3( x2 + perpDepth.x, y2+height, z2 + perpDepth.z );
	glm::vec3 tangent = vert1 - vert0;
	glm::vec3 bitangent = vert2 - vert0;
	glm::vec3 norm = glm::cross( tangent, bitangent );
	addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, color.x, color.y, color.z ); 
	addVert( vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, color.x, color.y, color.z ); 
	addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, color.x, color.y, color.z ); 

	addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, color.x, color.y, color.z ); 
	addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, color.x, color.y, color.z ); 
	addVert( vert0.x+perpDepth.x, vert0.y+height, vert0.z+perpDepth.z, norm.x, norm.y, norm.z,  color.x, color.y, color.z ); 
}

glm::vec3 Mesh::getCenter( ) {
	return center;
}

/**
* Set the value of uniforms
* @param new_var the new value of uniforms
*/
/*void setUniforms ( vector<GLDataObject *> new_var )     {
uniforms = new_var;
}*/

/**
* Get the value of uniforms
* @return the value of uniforms
*/
/*vector<GLDataObject *> getUniforms ( )     {
return uniforms;
}*/


void Mesh::initAttributes ( ) {
	dynamic = false;
}

