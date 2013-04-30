
#ifndef MESH_H
#define MESH_H

#include "glIncludes.h"
#include <vector>
#include <string>

#include "Component.h"
#include "Shader.h"
#include "Camera.h"

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

	Mesh ( Shader * shader ) { setShader( shader ); };

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


	void draw( Camera * camera ) {
		bindBuffers( );
		glm::mat4 modelCam = camera->cam * modelView;

		modelView = glm::mat4( );
		modelView = translations * rotations * scaling;

		glm::mat3 normalMatrix(modelCam);
		normalMatrix = glm::inverse(normalMatrix);
		normalMatrix = glm::transpose(normalMatrix);

		glUseProgram(shader->program);

		glUniformMatrix4fv(shader->modelViewLoc, 1, GL_FALSE, glm::value_ptr(modelCam));
		glUniformMatrix4fv(shader->projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->proj));
		glUniformMatrix3fv(shader->normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		glUniform3fv( shader->lightPosLoc, 1, glm::value_ptr(camera->lightPos));

		glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer); 
		glEnableVertexAttribArray(shader->vertexLoc); 
		glVertexAttribPointer(shader->vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, shader->normalBuffer);
		glEnableVertexAttribArray(shader->normalLoc);
		glVertexAttribPointer(shader->normalLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, shader->colorBuffer);
		glEnableVertexAttribArray(shader->colorLoc);
		glVertexAttribPointer(shader->colorLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		//draw the vertices/normals we just specified.
		glDrawArrays(GL_TRIANGLES, 0, numVerts);
	}

	/**
	* @param  x
	* @param  y
	* @param  z
	*/
	void translate (float x, float y, float z )
	{
		translations = glm::mat4();
		translations = glm::translate( glm::mat4( ), glm::vec3( x, y, z ) );
	}


	/**
	* @param  dir
	* @param  up
	*/
	void rotate (float angle, glm::vec3 axis)
	{
		rotations = glm::rotate( glm::mat4( ), angle, axis );
	}

	/**
	*
	*
	*/
	void rotate( float x, float y, float z ) {
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
	void scale (float x, float y, float z )
	{
		scaling = glm::scale( glm::mat4( ), glm::vec3( x, y, z ) );
	}

public:
	static const int VERT_SIZE;
	static const int UV_SIZE;

	Shader * shader;
	vector<float> verts;
	vector<float> norms;
	vector<float> colors;
	vector<GLuint> textureNames;

	size_t numVerts;
	glm::mat4 modelView; //matrices for shaders
	//vector<GLDataObject *> uniforms;
	// Private attribute accessor methods
	//  

	void setShader ( Shader * new_var )     {
		shader = new_var;
		shader->modelViewLoc = glGetUniformLocation(shader->program, "M");
		shader->projectionLoc = glGetUniformLocation(shader->program, "P");
		shader->normalMatLoc = glGetUniformLocation(shader->program, "M_n");
		shader->lightPosLoc = glGetUniformLocation(shader->program, "lightPos");

		shader->vertexLoc = glGetAttribLocation(shader->program, "pos");
		shader->normalLoc = glGetAttribLocation(shader->program, "norm");
		shader->colorLoc = glGetAttribLocation(shader->program, "color");

		GLuint bufs[3];
		glGenBuffers(3, bufs);

		shader->vertexBuffer = bufs[0];
		shader->normalBuffer = bufs[1];
		shader->colorBuffer = bufs[2];

		bindBuffers( );
	}

	void remove ( ) {
		verts.erase( verts.begin( ), verts.end( ) );
		norms.erase( norms.begin( ), norms.end( ) );
		colors.erase( colors.begin( ), colors.end( ) );
		textureNames.erase( textureNames.begin( ), textureNames.end( ) );
	}

	/**
	* Set the value of verts
	* @param new_var the new value of verts
	*/
	void setVerts ( vector<float> new_var )     {
		verts = new_var;
	}

	/**
	* Get the value of verts
	* @return the value of verts
	*/
	vector<float> getVerts ( )     {
		return verts;
	}

	/**
	* Set the value of norms
	* @param new_var the new value of norms
	*/
	void setNorms ( vector<float> new_var )     {
		norms = new_var;
	}

	/**
	* Get the value of norms
	* @return the value of norms
	*/
	vector<float> getNorms ( )     {
		return norms;
	}

	/**
	* Set the value of numVerts
	* @param new_var the new value of numVerts
	*/
	void setNumVerts ( size_t new_var )     {
		numVerts = new_var;
	}

	/**
	* Get the value of numVerts
	* @return the value of numVerts
	*/
	size_t getNumVerts ( )     {
		return numVerts;
	}

	/**
	* Set the value of textureNames
	* @param new_var the new value of textureNames
	*/
	void setTextureNames ( vector<GLuint> new_var )     {
		textureNames = new_var;
	}

	/**
	* Get the value of textureNames
	* @return the value of textureNames
	*/
	vector<GLuint> getTextureNames ( )     {
		return textureNames;
	}

	/**
	* Set the value of colors
	* @param new_var the new value of colors
	*/
	void setColors ( vector<float> new_var )     {
		colors = new_var;
	}

	/**
	* Get the value of colors
	* @return the value of colors
	*/
	vector<float> getColors ( )     {
		return colors;
	}

	void addVert (float x, float y, float z, float r, float g, float b){
		float nx = 0, ny = 0, nz = 0;
		//Calculate normal from previous verts if possible
		addVert (x,y,z,nx,ny,nz, r, g, b);
	}

	void addVert (float x, float y, float z, float nx, float ny, float nz, float r, float g, float b){
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

	void createYCube( float depth, float height, 
		glm::vec3 vert0, glm::vec3 vert1, 
		glm::vec3 color ) {
			glm::vec3 vert2 = glm::vec3( vert1.x, vert1.y + height, vert1.z );
			glm::vec3 tangent = vert1 - vert0;
			glm::vec3 bitangent = vert2 - vert0;
			glm::vec3 norm = glm::normalize( glm::cross( tangent, bitangent ) );

			glm::vec3 perpDepth = glm::vec3 ( -norm.x * depth, -norm.y, -norm.z * depth );
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

private:
	glm::mat4 translations;
	glm::mat4 rotations;
	glm::mat4 scaling;

	void bindBuffers( ) {
		//Create buffers for the vertex and normal attribute arrays

		glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float),verts.data(), GL_DYNAMIC_DRAW );

		glBindBuffer(GL_ARRAY_BUFFER, shader->normalBuffer);
		glBufferData( GL_ARRAY_BUFFER,norms.size() * sizeof(float),norms.data(),GL_DYNAMIC_DRAW );

		glBindBuffer(GL_ARRAY_BUFFER, shader->colorBuffer);
		glBufferData( GL_ARRAY_BUFFER,colors.size() * sizeof(float),colors.data(),GL_DYNAMIC_DRAW );

		numVerts = verts.size() / 3;
	}
	void initAttributes ( ) ;

};

#endif // MESH_H
