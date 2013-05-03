#ifndef MESHBATCH_H
#define MESHBATCH_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <string>

#include "Shader.h"

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

public:

	Shader * shader;
	vector<float> verts;
	vector<float> norms;
	size_t numVerts;
	glm::mat4 modelView, projection, camera; //matrices for shaders

	void draw( ) {
		bindBuffers( );
		glm::mat4 modelCam = camera * modelView;

		glm::mat3 normalMatrix(modelCam);
		normalMatrix = glm::inverse(normalMatrix);
		normalMatrix = glm::transpose(normalMatrix);

		glUseProgram(shader->program);

		glUniformMatrix4fv(shader->modelViewLoc, 1, GL_FALSE, glm::value_ptr(modelCam));
		glUniformMatrix4fv(shader->projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix3fv(shader->normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));


		glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer); 
		glEnableVertexAttribArray(shader->vertexLoc); 
		glVertexAttribPointer(shader->vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		//same procedure for the normal array
		glBindBuffer(GL_ARRAY_BUFFER, shader->normalBuffer);
		glEnableVertexAttribArray(shader->normalLoc);
		glVertexAttribPointer(shader->normalLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		//draw the vertices/normals we just specified.
		glDrawArrays(GL_TRIANGLES, 0, numVerts);
	}

	/**
	* Set the value of shader
	* @param new_var the new value of shader
	*/
	void setShader ( Shader * new_var )     {
		shader = new_var;
		shader->modelViewLoc = glGetUniformLocation(shader->program, "M");
		shader->projectionLoc = glGetUniformLocation(shader->program, "P");
		shader->normalMatLoc = glGetUniformLocation(shader->program, "M_n");

		shader->vertexLoc = glGetAttribLocation(shader->program, "pos");
		shader->normalLoc = glGetAttribLocation(shader->program, "norm");
	}

	/**
	* Get the value of shader
	* @return the value of shader
	*/
	Shader * getShader ( )     {
		return shader;
	}

	void bindBuffers( ) {
		//Create buffers for the vertex and normal attribute arrays
		GLuint bufs[2];
		glGenBuffers(2, bufs);

		shader->vertexBuffer = bufs[0];
		shader->normalBuffer = bufs[1];

		glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float),verts.data(), GL_STATIC_DRAW );

		glBindBuffer(GL_ARRAY_BUFFER, shader->normalBuffer);
		glBufferData( GL_ARRAY_BUFFER,norms.size() * sizeof(float),norms.data(),GL_STATIC_DRAW );

		numVerts = verts.size() / 3;
	}

private:



};

#endif MESHBATCH_H