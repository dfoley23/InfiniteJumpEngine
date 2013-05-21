#pragma once
#ifndef MESH_H
#define MESH_H

#include "glIncludes.h"

#include "Component.h"
#include "MeshBatch.h"

class MeshBatch;

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

	//Fields
	static const int VERT_SIZE;
	static const int UV_SIZE;

	vector<float> verts;
	vector<float> norms;
	vector<float> colors;
	vector<float> texCoords;
	vector<float> pickColors;
	vector<GLuint> textureNames;
	glm::mat4 modelView;
	glm::mat4 translations;
	glm::mat4 rotations;
	glm::mat4 scaling;
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 minXPoint;
	glm::vec3 minYPoint;
	glm::vec3 minZPoint;
	glm::vec3 maxXPoint;
	glm::vec3 maxYPoint;
	glm::vec3 maxZPoint;
	glm::vec3 center;
	size_t numVerts;
	int dynamic;
	int smooth;

	/**
	* @param  meshFile
	*/
	void createMesh (string meshFile );

	void draw( MeshBatch * batch );

	void drawForPick( MeshBatch * batch, glm::vec3 pickColors );

	void translate (float x, float y, float z );

	void rotate (float angle, glm::vec3 axis);

	void rotate( float x, float y, float z );

	void scale (float x, float y, float z );

	void remove ( );

	void bindBuffers( MeshBatch * batch, int picking );

	void setDynamic( int setting );

	void setSmooth( int setting );

	void addVert (float x, float y, float z, float r, float g, float b);

	void addVert (float x, float y, float z, 
		float nx, float ny, float nz, 
		float r, float g, float b, float u=0, float v=0);

	void createYCube( float depth, float height, 
		glm::vec3 vert0, glm::vec3 vert1, 
		glm::vec3 color );

	void createPlane( glm::vec3 perpDepth, float height, 
		float x1, float y1, float z1,
		float x2, float y2, float z2, glm::vec3 color );

	glm::vec3 getCenter( );
	
	glm::vec3 getMinPoint();

	glm::vec3 getMaxPoint();

	glm::vec3 getMinXPoint();

	glm::vec3 getMaxXPoint();

	glm::vec3 getMinYPoint();

	glm::vec3 getMaxYPoint();

	glm::vec3 getMinZPoint();

	glm::vec3 getMaxZPoint();

	vector<float> getVerts();

	void initAttributes( );

};

#endif MESH_H
