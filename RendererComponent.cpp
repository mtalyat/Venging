#include "RendererComponent.h"

RendererComponent::RendererComponent()
{
    meshToRender = new Mesh();
}

RendererComponent::~RendererComponent()
{
    delete(meshToRender);
}

Mesh* RendererComponent::createNewMesh()
{
    delete(meshToRender);
    meshToRender = new Mesh();
    return meshToRender;
}

Mesh* RendererComponent::mesh()
{
    return meshToRender;
}