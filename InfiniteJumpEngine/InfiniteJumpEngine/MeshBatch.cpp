#include "MeshBatch.h"

// Constructors/Destructors
//  

MeshBatch::~MeshBatch ( ) { 
	vector< vector<float> >().swap(verts);
	vector< vector<float> >().swap( norms);
	vector< vector<float> >().swap( colors);
	vector< vector<float> >().swap( texCoords);
	vector< glm::mat4 >().swap( modelViews );
	delete shader;
}

MeshBatch::MeshBatch ( Shader * shader ) { 
	verts.resize( 1 );
	norms.resize( 1 ); 
	colors.resize( 1 ); 
	texCoords.resize( 1 );
	modelViews.push_back( glm::mat4( ) );
	setShader( shader ); 	
};

/*
* draw all the compiled meshes
* seperating draw calls if dynamic transformations
*/
void MeshBatch::draw( ) {
	glUseProgram(shader->program);
	glUniformMatrix4fv(shader->projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(shader->viewLoc, 1, GL_FALSE, glm::value_ptr(cam));
	glUniform3fv( shader->lightPosLoc, 1, glm::value_ptr(lightPos));

	if ( texName.length() > 0 ) {
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);  
		glUniform1i(shader->textureLoc, 0);  
		glBindTexture(GL_TEXTURE_2D, Game::game()->resman->getTexture( texName ));  
	}

	int index = 0;
	for ( vecIter it = verts.begin(); it != verts.end(); ++it ) {
		bindBuffers( index );
		glm::mat4 modelCam = cam * modelViews.at( index );

		glm::mat3 normalMatrix(modelCam);
		normalMatrix = glm::inverse(normalMatrix);
		normalMatrix = glm::transpose(normalMatrix);

		glUniformMatrix4fv(shader->modelViewLoc, 1, GL_FALSE, glm::value_ptr(modelCam));
		glUniformMatrix3fv(shader->normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

		glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer); 
		glEnableVertexAttribArray(shader->vertexLoc); 
		glVertexAttribPointer(shader->vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, shader->normalBuffer);
		glEnableVertexAttribArray(shader->normalLoc);
		glVertexAttribPointer(shader->normalLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, shader->colorBuffer);
		glEnableVertexAttribArray(shader->colorLoc);
		glVertexAttribPointer(shader->colorLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);		

		glBindBuffer(GL_ARRAY_BUFFER, shader->texCoordBuffer);
		glEnableVertexAttribArray(shader->texCoordLoc);
		glVertexAttribPointer(shader->texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glDrawArrays(GL_TRIANGLES, 0, numVerts);

		(*it).clear( );
		verts.at( index ).clear();
		norms.at( index ).clear();
		colors.at( index ).clear();
		texCoords.at( index ).clear();
		index++;
	}
	if ( texName.length() > 0 ) {
		//glDisable(GL_TEXTURE_2D);  
	}

	verts.clear( );
	verts.resize( 1 );
	norms.clear( );
	norms.resize( 1 );
	colors.clear( );
	colors.resize( 1 );
	texCoords.clear( );
	texCoords.resize( 1 );
	modelViews.clear( );
	modelViews.push_back( glm::mat4( ) );
}


/**
* @param  x
* @param  y
* @param  z
*/
void MeshBatch::translate (float x, float y, float z )
{
	translations = glm::mat4();
	translations = glm::translate( glm::mat4( ), glm::vec3( x, y, z ) );
}


/**
* @param  dir
* @param  up
*/
void MeshBatch::rotate (float angle, glm::vec3 axis)
{
	rotations = glm::rotate( glm::mat4( ), angle, axis );
}

/**
*
*
*/
void MeshBatch::rotate( float x, float y, float z ) {
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
void MeshBatch::scale (float x, float y, float z )
{
	scaling = glm::scale( glm::mat4( ), glm::vec3( x, y, z ) );
}

void MeshBatch::setShader ( Shader * new_var )     {
	shader = new_var;
	shader->modelViewLoc = glGetUniformLocation(shader->program, "M");
	shader->viewLoc = glGetUniformLocation(shader->program, "V");
	shader->projectionLoc = glGetUniformLocation(shader->program, "P");
	shader->normalMatLoc = glGetUniformLocation(shader->program, "M_n");
	shader->lightPosLoc = glGetUniformLocation(shader->program, "lightPos");

	shader->textureLoc = glGetUniformLocation(shader->program, "tex"); 

	shader->vertexLoc = glGetAttribLocation(shader->program, "pos");
	shader->normalLoc = glGetAttribLocation(shader->program, "norm");
	shader->texCoordLoc = glGetAttribLocation(shader->program, "texCoord");
	shader->colorLoc = glGetAttribLocation(shader->program, "color");

	GLuint bufs[4];
	glGenBuffers(4, bufs);

	shader->vertexBuffer = bufs[0];
	shader->normalBuffer = bufs[1];
	shader->colorBuffer = bufs[2];
	shader->texCoordBuffer = bufs[3];

	bindBuffers( 0 );
}

/**
* Get the value of shader
* @return the value of shader
*/
Shader * MeshBatch::getShader ( )     {
	return shader;
}

glm::vec3 MeshBatch::getPickColors( ) {
	return pickColors;
}

void MeshBatch::bindBuffers( int pass ) {
	//Create buffers for the vertex and normal attribute arrays

	glBindBuffer(GL_ARRAY_BUFFER, shader->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verts.at(pass).size() * sizeof(float),verts.at(pass).data(), GL_DYNAMIC_DRAW );

	glBindBuffer(GL_ARRAY_BUFFER, shader->normalBuffer);
	glBufferData( GL_ARRAY_BUFFER,norms.at(pass).size() * sizeof(float),norms.at(pass).data(),GL_DYNAMIC_DRAW );

	glBindBuffer(GL_ARRAY_BUFFER, shader->colorBuffer);
	glBufferData( GL_ARRAY_BUFFER,colors.at(pass).size() * sizeof(float),colors.at(pass).data(),GL_DYNAMIC_DRAW );

	glBindBuffer(GL_ARRAY_BUFFER, shader->texCoordBuffer);
	glBufferData( GL_ARRAY_BUFFER,texCoords.at(pass).size() * sizeof(float),texCoords.at(pass).data(),GL_DYNAMIC_DRAW );

	numVerts = verts.at(pass).size() / 3;
}



