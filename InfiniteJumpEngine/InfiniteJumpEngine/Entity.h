
#ifndef ENTITY_H
#define ENTITY_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <string>
#include <vector>

#include "Component.h"
#include "Mesh.h"
#include "Camera.h"

using namespace std;

/**
  * class Entity
  * 
  */

class Entity : Component
{
public:

    // Constructors/Destructors
    //  
    /**
     * Empty Constructor
     */
    Entity ( );
    /**
     * Empty Destructor
     */
    virtual ~Entity ( );

	void update( float dT );
	void draw( Camera * camera );
	void remove( );

    /**
     * Set the value of mesh
     * @param new_var the new value of mesh
     */
    void addComponent ( Component *new_var )     {
		components.push_back(new_var);
		new_var->setParent(this);
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
protected:

	
    // Static Protected attributes
    //  

	// Protected methods
	//
	void initAttributes ( ) ;

    // Protected attributes
    //  
	componentVector components;
    glm::vec3 center;

};

#endif // ENTITY_H
