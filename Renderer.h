#ifndef RENDERER_H
#define RENDERER_H

#include <cstdbool>
#include "Component.h"
#include "Mesh.h"

class Renderer
	: public Component
{
public:
	/// <summary>
	/// Creates a new Renderer.
	/// </summary>
	Renderer();

	~Renderer();

	/// <summary>
	/// Deletes the old Mesh and returns a new Mesh.
	/// </summary>
	/// <returns></returns>
	Mesh* createNewMesh();

	/// <summary>
	/// Returns the current stored Mesh.
	/// </summary>
	/// <returns></returns>
	Mesh* mesh();
private:
	Mesh* meshToRender;
};

#endif
