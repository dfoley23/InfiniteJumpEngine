
#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include "Edge.h"
using namespace std;
/**
  * class Tile
  * 
  */

class Tile
{
public:	
    // Constructors/Destructors
    //  


    /**
     * Empty Constructor
     */
    Tile ( );

    /**
     * Empty Destructor
     */
    virtual ~Tile ( );

    // Static Public attributes
    //  
	static const int GROUND_VERTS;

    // Public attributes
    //  


    // Public attribute accessor methods
    //  


    // Public attribute accessor methods
    //  
	vector<float> getVerts();

protected:

    // Static Protected attributes
    //  
	const vector<Tile*> tiles;

    // Protected attributes
    //  
	float **groundVerts;

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

    vector<Edge> edges;
public:


    // Private attribute accessor methods
    //  

private:

public:


    // Private attribute accessor methods
    //  


    /**
     * Set the value of edges
     * @param new_var the new value of edges
     */
    void setEdges ( vector<Edge> new_var )     {
            edges = new_var;
    }

    /**
     * Get the value of edges
     * @return the value of edges
     */
    vector<Edge> getEdges ( ) {
        return edges;
    }
private:


    void initAttributes ( ) ;

};

#endif // TILE_H
