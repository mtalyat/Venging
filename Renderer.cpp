#include "Renderer.h"

Renderer::Renderer()
{
    meshToRender = new Mesh();
}

Renderer::~Renderer()
{
    delete(meshToRender);
}

Mesh* Renderer::createNewMesh()
{
    delete(meshToRender);
    meshToRender = new Mesh();
    return meshToRender;
}

Mesh* Renderer::mesh()
{
    return meshToRender;
}