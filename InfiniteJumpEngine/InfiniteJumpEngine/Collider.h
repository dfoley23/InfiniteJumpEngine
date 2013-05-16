#pragma once
#include "Component.h"
#include "Mesh.h"
#include "glIncludes.h"
/*
 * References
 * Point-in-triangle formula: http://www.blackpawn.com/texts/pointinpoly/
*/

class Collider : public Component
{
public:
	Collider(void);
	~Collider(void);

	/*
		Overloaded setParent functions allow us to tell whether the parent of this collider is another collider.
	*/
	void setParent(Collider* p){b_parentCollider = (p != NULL); parent = p;}
	void setParent(Component* p){b_parentCollider = false; parent = p;}

	/*
		Checks right-at-the-moment whether two colliders are overlapping.
	*/
	virtual bool isColliding(Collider*){return false;};
	bool isCollidingRecursive(Collider*);

	bool sameSideOfLine(glm::vec3, glm::vec3, glm::vec3, glm::vec3); 

	bool inTriangleBounds( glm::vec3, glm::vec3, glm::vec3 );
	/*
		Checks if and when two colliders will ever collide in the near future.
		bool - Will these two ever collide?
		float - If so, when?
	*/
	virtual pair<bool,float> predictCollision(Collider*){return pair<bool,float>(false, 0.0f);};
	pair<bool,float> predictCollisionRecursive(Collider*);
protected:
	//Is the parent of this collider another collider or not?
	bool b_parentCollider;
};

