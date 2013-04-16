
#ifndef ENTITY_H
#define ENTITY_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <string>

#include "Mesh.h"
using namespace std;

/**
  * class Entity
  * 
  */

class Entity
{
public:

    // Constructors/Destructors
    //  


    /**
     * Empty Constructor
     */
    Entity ( );
	Entity ( string name ) { mesh = new Mesh( ); }
    /**
     * Empty Destructor
     */
    virtual ~Entity ( );

    // Static Public attributes
    //  

    // Public attributes
    //  


    // Public attribute accessor methods
    //  


    // Public attribute accessor methods
    //  


protected:

    // Static Protected attributes
    //  

    // Protected attributes
    //  

public:


    // Protected attribute accessor methods
    //  

protected:

public:


    // Protected attribute accessor methods
    //  

protected:


private:

    // Static Private attributes
    //  

    // Private attributes
    //  

    glm::vec3 center;
public:
	
    Mesh* mesh;

    // Private attribute accessor methods
    //  

private:

public:

	void draw( MeshBatch * batch ) {
		mesh->draw( batch );
	}

    /**
     * Set the value of mesh
     * @param new_var the new value of mesh
     */
    void setMesh ( Mesh * new_var )     {
            mesh = new_var;
    }

    /**
     * Get the value of mesh
     * @return the value of mesh
     */
    Mesh * getMesh ( )     {
        return mesh;
    }

    /**
     * Set the value of center
     * @param new_var the new value of center
     */
    void setCenter ( glm::vec3 new_var )     {
            center = new_var;
    }

    /**
     * Get the value of center
     * @return the value of center
     */
    glm::vec3 getCenter ( )     {
        return center;
    }
private:


    void initAttributes ( ) ;

};

#endif // ENTITY_H
