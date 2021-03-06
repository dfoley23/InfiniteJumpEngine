#pragma once
#ifndef RESMANAGER_H
#define RESMANAGER_H

#include <sstream>
#include <map>

#include "glIncludes.h"
#include "loadpng.h"

#include "Tile.h"
#include "Ball.h"
#include "Entity.h"
#include "Level.h"
#include "TileSet.h"

class Level;

class ResManager: public Component
{
public:
	ResManager(void);
	~ResManager(void);
	Level *getTriangleLevel(string filename, int holeID);
	Mesh *readObjFile(string filename);
	void writeScoreFile( string filename, string scores );
	string readScoreFile( string filename );
	void loadTextureList( string filename );
	GLuint getTexture( string id );
	void clearTextures( );
private:
	void loadTexture(const char * filename, string id);
	map< string, GLuint > textures;
};

#endif RESMANAGER_H