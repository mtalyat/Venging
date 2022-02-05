#ifndef RENDERER_H
#define RENDERER_H

#include <cstdbool>
#include "Component.h"
#include "Mesh.h"

class RendererComponent
	: public Component
{
public:
	/// <summary>
	/// Creates a new Renderer.
	/// </summary>
	RendererComponent();

	~RendererComponent();

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
