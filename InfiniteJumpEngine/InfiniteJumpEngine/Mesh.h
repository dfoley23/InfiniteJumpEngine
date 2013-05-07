
#ifndef MESH_H
#define MESH_H

#include "glIncludes.h"
#include <vector>
#include <string>

#include "Component.h"
#include "Shader.h"
#include "Camera.h"
#include "MeshBatch.h"

using namespace std;
/**
* class Mesh
* 
*/

class Mesh: public Component {
public:

	// Constructors/Destructors
	//  


	/**
	* Empty Constructor
	*/
	Mesh ( );

	/**
	* Empty Destructor
	*/
	virtual ~Mesh ( );

	/**
	* @param  meshFile
	*/
	void createMesh (string meshFile )
	{
	}


	void draw( MeshBatch * batch ) {
		for(int i=0; i < static_cast<int>(verts.size()); i++) {
			batch->verts.push_back( verts.at(i) );
			batch->norms.push_back( norms.at(i) );
			batch->colors.push_back( colors.at(i) );
		}
	}

	void translate (float x, float y, float z )
	{
		glm::mat4 t_m = glm::translate( glm::mat4( ), glm::vec3( x, y, z ) );
		for(int i=0; i < static_cast<int>(verts.size()); i++) {
			glm::vec4 oldVec = glm::vec4( verts.at(i), verts.at(i+1), verts.at(i+2), 1.0 );
			glm::vec4 transVec = t_m * oldVec;
			verts.at(i) = transVec.x;
			verts.at(i+1) = transVec.y;
			verts.at(i+2) = transVec.z;
			i+=2;
		}
	}

	void translateX (float x )
	{
		for(int i=0; i < static_cast<int>(verts.size()); i++) {
			verts.at(i) = originVerts.at(i) + x;
			i+=2;
		}
	}

	void translateY (float y )
	{
		for(int i=1; i < static_cast<int>(verts.size()); i++) {
			verts.at(i) = originVerts.at(i) + y;
			i+=2;
		}
	}

	void translateZ (float z )
	{
		for(int i=2; i < static_cast<int>(verts.size()); i++) {
			verts.at(i) = originVerts.at(i) + z;
			i+=2;
		}
	}
	void rotate( float x, float y, float z ) {
		glm::mat4 rX = glm::rotate( glm::mat4( ), x, glm::vec3( 1, 0, 0 ) );
		glm::mat4 rY = glm::rotate( glm::mat4( ), y, glm::vec3( 0, 1, 0 ) );
		glm::mat4 rZ = glm::rotate( glm::mat4( ), z, glm::vec3( 0, 0, 1 ) );
		glm::mat4 r = rX * rY * rZ;
		for(int i=0; i < static_cast<int>(verts.size()); i++) {
			glm::vec4 oldVec = glm::vec4( verts.at(i), verts.at(i+1), verts.at(i+2), 0.0 );
			glm::vec4 oldNorm = glm::vec4( norms.at(i), norms.at(i+1), norms.at(i+2), 0.0 );
			glm::vec4 rotVec = r * oldVec;
			glm::vec4 rotNorm = r * oldNorm;
			verts.at(i) = rotVec.x;
			verts.at(i+1) = rotVec.y;
			verts.at(i+2) = rotVec.z;
			norms.at(i) = rotNorm.x;
			norms.at(i+1) = rotNorm.y;
			norms.at(i+2) = rotNorm.z;
			i+=2;
		}
	}

public:
	static const int VERT_SIZE;
	static const int UV_SIZE;

	vector<float> verts;
	vector<float> norms;
	vector<float> colors;
	vector<float> texCoords;
	vector<GLuint> textureNames;
	vector<float> originVerts;
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 center;

	void remove ( ) {
		verts.erase( verts.begin( ), verts.end( ) );
		norms.erase( norms.begin( ), norms.end( ) );
		colors.erase( colors.begin( ), colors.end( ) );
		textureNames.erase( textureNames.begin( ), textureNames.end( ) );
	}

	void addVert (float x, float y, float z, float r, float g, float b){
		float nx = 0, ny = 0, nz = 0;
		//Calculate normal from previous verts if possible
		addVert (x,y,z,nx,ny,nz, r, g, b);
	}

	void addVert (float x, float y, float z, float nx, float ny, float nz, float r, float g, float b){
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
		originVerts.push_back(x);
		originVerts.push_back(y);
		originVerts.push_back(z);
		norms.push_back(nx);
		norms.push_back(ny);
		norms.push_back(nz);
		colors.push_back(r);
		colors.push_back(g);
		colors.push_back(b);

	}

	void createYCube( float depth, float height, 
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

	void createPlane( glm::vec3 perpDepth, float height, float x1, float y1, float z1, float x2, float y2, float z2, glm::vec3 color ) {
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

	glm::vec3 getCenter( ) {
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

	void initAttributes ( ) ;

};

#endif // MESH_H
