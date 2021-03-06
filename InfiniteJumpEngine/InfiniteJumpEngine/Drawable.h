#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Updatable.h"

class MeshBatch;

class Drawable: public Updatable
{
public:
	virtual void draw(MeshBatch *){};
	virtual void drawForPick(MeshBatch *, glm::vec3 pickColors){};
	virtual long drawOrder(){ return 0; };
	virtual bool compareDrawOrder(){ return false; };
};

#endif DRAWABLE_H