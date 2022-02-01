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
#include "ColorPalette.h"
#include "Color.h"

class RenderingSystem :
    public System
{
public:
    RenderingSystem();
    ~RenderingSystem();

    /// <summary>
    /// Renders the stored renderers onto the given Window.
    /// </summary>
    /// <param name="window"></param>
    void render(Window* window);

    void init() override;

    void addEntity(Entity* entity) override;
    bool removeEntity(Entity* entity) override;

private:
    List<Renderer*> renderers;

    //open gl stuff
    Shader* shaderProgram;

    ColorPalette* palette;
};

#endif
