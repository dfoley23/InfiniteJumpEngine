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
		//render( batch, 1 );
		batch->verts.resize( batch->verts.size( ) + 1 );
		batch->norms.resize( batch->norms.size( ) + 1 );
		batch->colors.resize( batch->colors.size( ) + 1 );
		index = static_cast<int>(batch->verts.size( )) - 1;
		modelView = glm::mat4( );
		modelView = translations * rotations * scaling * transform(); 
		batch->modelViews.push_back( modelView );
		batch->verts.at(index).insert( batch->verts.at(index).end(), verts.begin(), verts.end() );
		batch->norms.at(index).insert( batch->norms.at(index).end(), norms.begin(), norms.end() );
		batch->colors.at(index).insert( batch->colors.at(index).end(), colors.begin(), colors.end() );
	} else {
		batch->verts.at(index).insert( batch->verts.at(index).end(), verts.begin(), verts.end() );
		batch->norms.at(index).insert( batch->norms.at(index).end(), norms.begin(), norms.end() );
		batch->colors.at(index).insert( batch->colors.at(index).end(), colors.begin(), colors.end() );
	}
}

void Mesh::drawForPick( MeshBatch * batch, glm::vec3 id ) {
	pickId.x = id.x;
	pickId.y = id.y;
	pickId.z = id.z;
	int index = 0;
	if ( dynamic ) {	
		//render( batch, 0 );
		batch->verts.resize( batch->verts.size( ) + 1 );
		batch->norms.resize( batch->norms.size( ) + 1 );
		batch->colors.resize( batch->colors.size( ) + 1 );
		index = static_cast<int>(batch->verts.size( )) - 1;
		modelView = glm::mat4( );
		modelView = translations * rotations * scaling; 
		batch->modelViews.push_back( modelView );
		batch->verts.at(index).insert( batch->verts.at(index).end(), verts.begin(), verts.end() );
		batch->norms.at(index).insert( batch->norms.at(index).end(), norms.begin(), norms.end() );
		for(int i=0; i < static_cast<int>(verts.size()); i+=3) {
			batch->colors.at(index).push_back( id.x / 255.0f );
			batch->colors.at(index).push_back( id.y / 255.0f );
			batch->colors.at(index).push_back( id.z / 255.0f );
		}
	} else {
		batch->verts.at(index).insert( batch->verts.at(index).end(), verts.begin(), verts.end() );
		batch->norms.at(index).insert( batch->norms.at(index).end(), norms.begin(), norms.end() );
		for(int i=0; i < static_cast<int>(verts.size()); i+=3) {
			batch->colors.at(index).push_back( id.x / 255.0f );
			batch->colors.at(index).push_back( id.y / 255.0f );
			batch->colors.at(index).push_back( id.z / 255.0f );
		}
	}
}

void Mesh::render( MeshBatch * batch, int picking ) {
	glUseProgram(batch->shader->program);

	bindBuffers( batch, picking );
	glm::mat4 modelCam = batch->cam * modelView;

	glm::mat3 normalMatrix(modelCam);
	normalMatrix = glm::inverse(normalMatrix);
	normalMatrix = glm::transpose(normalMatrix);

	glUniformMatrix4fv(batch->shader->modelViewLoc, 1, GL_FALSE, glm::value_ptr(modelCam));
	glUniformMatrix4fv(batch->shader->projectionLoc, 1, GL_FALSE, glm::value_ptr(batch->proj));
	glUniformMatrix3fv(batch->shader->normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	glUniform3fv( batch->shader->lightPosLoc, 1, glm::value_ptr(batch->lightPos));

	glBindBuffer(GL_ARRAY_BUFFER, batch->shader->vertexBuffer); 
	glEnableVertexAttribArray(batch->shader->vertexLoc); 
	glVertexAttribPointer(batch->shader->vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, batch->shader->normalBuffer);
	glEnableVertexAttribArray(batch->shader->normalLoc);
	glVertexAttribPointer(batch->shader->normalLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, batch->shader->colorBuffer);
	glEnableVertexAttribArray(batch->shader->colorLoc);
	glVertexAttribPointer(batch->shader->colorLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, numVerts);
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
	center.x = x;
	center.y = y;
	center.z = z;
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

void Mesh::setDynamic( int setting ) {
	dynamic = setting;
}

void Mesh::setSmooth( int setting ) {
	smooth = setting;
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
	addVert (x, y ,z, nx, ny, nz, r, g, b);
}

void Mesh::addVert (float x, float y, float z, float nx, float ny, float nz, float r, float g, float b){
	if ( verts.empty( ) ) {
		min = glm::vec3 ( x, y, z );
		max = glm::vec3 ( x, y, z );
		center = glm::vec3( 0, 0, 0 );
		minXPoint = min;
		minYPoint = min;
		minZPoint = min;
		maxXPoint = max;
		maxYPoint = max;
		maxZPoint = max;
	} else {
		if ( x < minXPoint.x ) {
			minXPoint = glm::vec3 ( x, y, z );
		} else if ( x > maxXPoint.x ) {
			maxXPoint = glm::vec3 ( x, y, z );
		}
		if ( y < minYPoint.y ) {
			minYPoint = glm::vec3 ( x, y, z );
		} else if ( x > maxYPoint.y ) {
			maxYPoint = glm::vec3 ( x, y, z );
		}
		if ( z < minZPoint.z ) {
			minZPoint = glm::vec3 ( x, y, z );
		} else if ( x > maxZPoint.z ) {
			maxZPoint = glm::vec3 ( x, y, z );
		}
		if ( x < min.x ) {
			min.x = x;
		} else if ( x > max.x ) {
			max.x = x;
		}
		if ( y < min.y ) {
			min.y = y;
		} else if ( y > max.y ) {
			max.y = y;
		}
		if ( z < min.z ) {
			min.z = z;
		} else if ( z > max.z ) {
			max.z = z;
		}		
	}
	center.x = (center.x + x) / static_cast<float>(verts.size());
	center.y = (center.y + y) / static_cast<float>(verts.size());
	center.z = (center.z + z) / static_cast<float>(verts.size());
	glm::vec3 vertexNormal = glm::vec3( 0, 0, 0 );
	if ( smooth ) {
		vector<int> sharedNorms;
		for ( int i=0; i<static_cast<int>(norms.size())-2; i++ ) {
			if ( verts.at( i ) == x && verts.at( i+1 ) == y && verts.at( i+2 ) == z ) {
				if ( static_cast<int>(sharedNorms.size()) == 0 ) {
					vertexNormal.x = norms.at( i );
					vertexNormal.y = norms.at( i+1 );
					vertexNormal.z = norms.at( i+2 );
				}
				sharedNorms.push_back( i );
			}
			i+=2;
		}
		for( int i=0; i<static_cast<int>(sharedNorms.size()); i++ ) {
			norms.at( sharedNorms.at( i ) ) = (vertexNormal.x + nx)/2.0f;
			norms.at( sharedNorms.at( i )+1 ) = (vertexNormal.y + ny)/2.0f;
			norms.at( sharedNorms.at( i )+2 ) = (vertexNormal.z + nz)/2.0f;
		}
	}
	vertexNormal.x += nx;
	vertexNormal.y += ny;
	vertexNormal.z += nz;
	verts.push_back(x);
	verts.push_back(y);
	verts.push_back(z);
	norms.push_back(vertexNormal.x);
	norms.push_back(vertexNormal.y);
	norms.push_back(vertexNormal.z);
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

vector<float> Mesh::getVerts(){
	return verts;
}

glm::vec3 Mesh::getMinXPoint() {
	return minXPoint;
}

glm::vec3 Mesh::getMaxXPoint() {
	return maxXPoint;
}

glm::vec3 Mesh::getMinYPoint() {
	return minYPoint;
}

glm::vec3 Mesh::getMaxYPoint() {
	return maxYPoint;
}

glm::vec3 Mesh::getMinZPoint() {
	return minZPoint;
}

glm::vec3 Mesh::getMaxZPoint() {
	return maxZPoint;
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

void Mesh::bindBuffers( MeshBatch * batch, int picking ) {
	//Create buffers for the vertex and normal attribute arrays

	glBindBuffer(GL_ARRAY_BUFFER, batch->shader->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float),verts.data(), GL_DYNAMIC_DRAW );

	glBindBuffer(GL_ARRAY_BUFFER, batch->shader->normalBuffer);
	glBufferData( GL_ARRAY_BUFFER,norms.size() * sizeof(float),norms.data(),GL_DYNAMIC_DRAW );

	glBindBuffer(GL_ARRAY_BUFFER, batch->shader->colorBuffer);
	if ( picking ) {
		glBufferData( GL_ARRAY_BUFFER,pickColors.size() * sizeof(float), pickColors.data(),GL_DYNAMIC_DRAW );
	} else {
		glBufferData( GL_ARRAY_BUFFER,colors.size() * sizeof(float),colors.data(),GL_DYNAMIC_DRAW );
	}

	numVerts = verts.size() / 3;
}

void Mesh::initAttributes ( ) {
	dynamic = 0;
	smooth = 0;
}

