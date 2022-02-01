#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include <GLFW/glfw3.h>
#include "System.h"
#include "Renderer.h"
#include "Console.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Window.h"
#include "Camera.h"

class RenderingSystem :
    public System
{
public:
    RenderingSystem();
    ~RenderingSystem();

    void render(Window* window);

    void addEntity(Entity* entity) override;
    bool removeEntity(Entity* entity) override;

private:
    List<Renderer*> renderers;

    //open gl stuff
    Shader* shaderProgram;
};

#endif
