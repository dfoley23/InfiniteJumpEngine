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
typedef vector< vector<float> >::iterator vecIter;

class MeshBatch
{
public:

	// Constructors/Destructors
	//  


	/**
	* Empty Constructor
	*/
	MeshBatch ( );
	MeshBatch ( Shader * );

	/**
	* Empty Destructor
	*/
	virtual ~MeshBatch ( );

	Shader * shader;
	vector< vector<float> > verts;
	vector< vector<float> > norms;
	vector< vector<float> > colors;
	vector< vector<float> > texCoords;
	vector< glm::mat4 > modelViews;
	size_t numVerts;
	glm::mat4 cam;
	glm::mat4 proj;
	glm::vec3 lightPos;

	void draw( );

	
	/**
	* @param  x
	* @param  y
	* @param  z
	*/
	void translate (float x, float y, float z );


	/**
	* @param  dir
	* @param  up
	*/
	void rotate (float angle, glm::vec3 axis);

	/**
	*
	*
	*/
	void rotate( float x, float y, float z );

	/**
	* @param  x
	* @param  y
	* @param  z
	*/
	void scale (float x, float y, float z );
	
	void setShader ( Shader * new_var );

	/**
	* Get the value of shader
	* @return the value of shader
	*/
	Shader * getShader ( );

	glm::vec3 getPickColors( );

private:
	glm::mat4 translations;
	glm::mat4 rotations;
	glm::mat4 scaling;
	glm::vec3 pickColors;

	void bindBuffers( int pass );

};

#endif MESHBATCH_H