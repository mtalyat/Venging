#include "Engine.h"
#include "Scene.h"
#include "Entity.h"
#include "Camera.h"
#include "Window.h"
#include "Console.h"
#include "Transform.h"

int main()
{
    Window* window = new Window(800, 800, "Test");
    window->setBackgroundColor(Color(0.2f, 0.56f, 0.85f));

    Engine* engine = new Engine(window);
    Scene* scene = new Scene();
    engine->addScene(scene);

    Entity* camEntity = new Entity();
    camEntity->transform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));
    Camera* cam = new Camera();
    camEntity->addComponent(cam);

    engine->run();
}