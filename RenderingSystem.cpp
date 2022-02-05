#include "RenderingSystem.h"

RenderingSystem::RenderingSystem()
{
	shaderProgram = new Shader("default.vert", "default.frag");
	palette = new ColorPalette("default.palette");
}

RenderingSystem::~RenderingSystem()
{
	shaderProgram->deleteProgram();

	delete shaderProgram;
	delete palette;
}

void RenderingSystem::render(Window* window)
{
	CameraComponent::main()->inputs(window, shaderProgram);
	CameraComponent::main()->matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix", window);

	//render each mesh in the rendering system
	int i = 0;
	for (; i < renderers.length(); i++)
	{
		renderers[i]->mesh()->render(renderers[i]->transform(), shaderProgram);
	}
}

void RenderingSystem::init()
{
	shaderProgram->setPalette(palette);
	shaderProgram->setFaceShades(1.0f, 0.8f, 0.6f, 0.4f);
}

void RenderingSystem::addEntity(Entity* entity)
{
	RendererComponent* r = entity->getComponent<RendererComponent>();

	if (r == NULL)
	{
		Console::LogWarning("The given entity did not have an attached Renderer Component.");
		return;
	}

	entities.add(entity);
	renderers.add(r);
}

bool RenderingSystem::removeEntity(Entity* entity)
{
	if (!System::removeEntity(entity))
	{
		//did not contain entity
		return false;
	}

	return renderers.remove(entity->getComponent<RendererComponent>());
}
