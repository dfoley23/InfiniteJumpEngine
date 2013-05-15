#pragma once
#include "Component.h"
#include "Mesh.h"
#include "glIncludes.h"
/*
 * References
 * Point-in-triangle formula: http://www.blackpawn.com/texts/pointinpoly/

 function SameSide(p1,p2, a,b)
    cp1 = CrossProduct(b-a, p1-a)
    cp2 = CrossProduct(b-a, p2-a)
    if DotProduct(cp1, cp2) >= 0 then return true
    else return false

function PointInTriangle(p, a,b,c)
    if SameSide(p,a, b,c) and SameSide(p,b, a,c)
        and SameSide(p,c, a,b) then return true
    else return false

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
	bool inVerticalBounds( glm::vec3, glm::vec3, glm::vec3 );

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

