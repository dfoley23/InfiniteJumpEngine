#include "TileSet.h"
#include "Camera.h"


TileSet::TileSet(void)
{
}


TileSet::~TileSet(void)
{
}

void TileSet::update(float dT){
if (!mesh){
mesh = createMesh();
}
if (mesh){
mesh->update(dT);
}
}

void TileSet::draw( Camera * camera ){
if (mesh){
mesh->draw(camera);
}
}

Mesh* TileSet::createMesh(){
return NULL;
}