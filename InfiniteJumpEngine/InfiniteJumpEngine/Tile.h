#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

class TileSet;

using namespace std;
/**
* class Tile
*
*/

class Tile
{
public:	
friend class TileSet;
    // Constructors/Destructors
    //

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
    /**
* Empty Constructor
*/
    Tile ( );

    // Static Protected attributes
    //
const vector<Tile*> tiles;

    // Protected attributes
    //
float **groundVerts;

private:


    void initAttributes ( ) ;

};

#endif // TILE_H