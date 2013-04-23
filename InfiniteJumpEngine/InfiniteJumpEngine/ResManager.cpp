#include "ResManager.h"

ResManager::ResManager(void)
{
}


ResManager::~ResManager(void)
{
}

Level* ResManager::getTriangleLevel(){
	Level *level = new Level();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	level->camera->cam = glm::lookAt(glm::vec3(0,6,6), glm::vec3(0,0,0), glm::vec3(0,1,0));
	level->camera->proj = glm::perspective(
		glm::float_t(45),
		glm::float_t(Game::game()->getWinWidth()) / glm::float_t(Game::game()->getWinHeight()),
		glm::float_t(0.1),
		glm::float_t(1000.0)
		);
	level->camera->lightPos = glm::vec3( 0.0, 10.0f, 0.0 );

	//initiallize vertex and normal arrays
	//this is where you might want to read in your model
	Entity * entity = new Entity( );
	Mesh * mesh = new Mesh( new Shader( "shaders/gles.vert", "shaders/gles.frag") );
	mesh->addVert(-1,0,1, 0,1,0, 0,1,0);
	mesh->addVert(1,0,1, 0,1,0, 0,1,0);
	mesh->addVert(1,0,-1, 0,1,0, 0,1,0);

	mesh->addVert(-1,0,1, 0,1,0, 0,1,0);
	mesh->addVert(1,0,-1, 0,1,0, 0,1,0);
	mesh->addVert(-1,0,-1, 0,1,0, 0,1,0);

	entity->addComponent(mesh);

	level->entities.push_back(entity);
	return level;
}