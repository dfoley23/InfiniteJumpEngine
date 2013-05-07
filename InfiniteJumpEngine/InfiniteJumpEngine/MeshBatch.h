#ifndef MESHBATCH_H
#define MESHBATCH_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <string>

#include "Shader.h"
#include "Camera.h"

using namespace std;
/**
* class MeshBatch
* 
*/

class MeshBatch
{
public:

	// Constructors/Destructors
	//  


	/**
	* Empty Constructor
	*/
	MeshBatch ( );
	MeshBatch ( Shader * shader ) { setShader( shader ); };
	/**
	* Empty Destructor
	*/
	virtual ~MeshBatch ( );

	Shader * shader;
	vector<float> verts;
	vector<float> norms;
	vector<float> colors;
	vector<float> texCoords;
	size_t numVerts;
	glm::mat4 modelView; //matrices for shaders
	glm::mat4 cam;
	glm::mat4 proj;
	glm::vec3 lightPos;

	void draw( ) {
		bindBuffers( );
		glm::mat4 modelCam = cam * modelView;

		glm::mat3 normalMatrix(modelCam);
		normalMatrix = glm::inverse(normalMatrix);
		normalMatrix = glm::transpose(normalMatrix);

		glUseProgram(shader->program);

		glUniformMatrix4fv(shader->modelViewLoc, 1, GL_FALSE, glm::value_ptr(modelCam));
		glUniformMatrix4fv(shader->projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));
		glUniformMatrix3fv(shader->normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		glUniform3fv( shader->lightPosLoc, 1, glm::value_ptr(lightPos));


		glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer); 
		glEnableVertexAttribArray(shader->vertexLoc); 
		glVertexAttribPointer(shader->vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		//same procedure for the normal array
		glBindBuffer(GL_ARRAY_BUFFER, shader->normalBuffer);
		glEnableVertexAttribArray(shader->normalLoc);
		glVertexAttribPointer(shader->normalLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		

		glBindBuffer(GL_ARRAY_BUFFER, shader->colorBuffer);
		glEnableVertexAttribArray(shader->colorLoc);
		glVertexAttribPointer(shader->colorLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		//draw the vertices/normals we just specified.
		glDrawArrays(GL_TRIANGLES, 0, numVerts);

		verts.clear( );
		norms.clear( );
		colors.clear( );
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

	/**
	* Get the value of shader
	* @return the value of shader
	*/
	Shader * getShader ( )     {
		return shader;
	}

	void updatePickColors( ) {
		pickColors.x++;
		if ( pickColors.x > 255 ) {
			pickColors.x = 0; 
			pickColors.y++;
			if ( pickColors.y > 255 ) {
				pickColors.y = 0;
				pickColors.z++;
			}
		}
	}

	glm::vec3 getPickColors( ) {
		return pickColors;
	}

private:
	glm::mat4 translations;
	glm::mat4 rotations;
	glm::mat4 scaling;
	glm::vec3 pickColors;

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



};

#endif MESHBATCH_H