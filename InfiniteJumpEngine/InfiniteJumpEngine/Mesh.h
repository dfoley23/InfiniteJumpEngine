
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h> //must include this before gl.h
#include <GL/freeglut.h>
#include <GL/gl.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <vector>
#include <string>

#include "MeshBatch.h"
using namespace std;
/**
  * class Mesh
  * 
  */

class Mesh
{
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


    /**
     * @param  batch
     */
    void draw (MeshBatch * batch )
    {
		for(std::vector<float>::size_type i = 0; i != verts.size(); i++) {
			batch->verts.push_back( verts.at(i) );
		}
		for(std::vector<float>::size_type i = 0; i != norms.size(); i++) {
			batch->norms.push_back( norms.at(i) );
		}
    }


    /**
     * @param  x
     * @param  y
     * @param  z
     */
    void translate (float x, float y, float z )
    {
    }


    /**
     * @param  dir
     * @param  up
     */
    void rotate (glm::vec3 dir, glm::vec3 up )
    {
    }


    /**
     * @param  x
     * @param  y
     * @param  z
     */
    void scale (float x, float y, float z )
    {
    }

private:

public:

    vector<float> verts;
    vector<float> norms;
    size_t numVerts;
    vector<GLuint> textureNames;
    vector<float> colors;
    //vector<GLDataObject *> uniforms;
    // Private attribute accessor methods
    //  

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


    void initAttributes ( ) ;

};

#endif // MESH_H
