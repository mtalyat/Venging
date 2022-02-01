#ifndef RENDERER_H
#define RENDERER_H

#include <cstdbool>
#include "Component.h"
#include "Mesh.h"

class Renderer
	: public Component
{
public:
	Renderer();
	~Renderer();

	Mesh* createNewMesh();
	Mesh* mesh();
private:
	Mesh* meshToRender;
};

#endif
