#include "Engine.h"
#include "Scene.h"
#include "Entity.h"
#include "Camera.h"
#include "Window.h"
#include "Console.h"
#include "Transform.h"
#include "Chunk.h"
#include "RenderingSystem.h"
#include "ChunkSystem.h"

int main()
{
    //setup engine
    Window* window = new Window(800, 800, "Test");
    window->setBackgroundColor(Color::gray());

    Engine* engine = new Engine(window);
    Scene* scene = new Scene();
    engine->addScene(scene);

    Entity* camEntity = new Entity();
    camEntity->transform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));
    Camera* cam = new Camera();
    camEntity->addComponent(cam);

    //rendering
    RenderingSystem* rs = new RenderingSystem();
    scene->addSystem(rs);

    //mesh
    Entity* meshEntity = new Entity();
    Renderer* meshRenderer = new Renderer();
    meshEntity->addComponent(meshRenderer);
    rs->addEntity(meshEntity);

    //create a chunk
    //Entity* chunkEntity = new Entity();
    //Chunk* chunk = new Chunk();
    //chunkEntity->addComponent(chunk);
    //chunk->set(1, 1, 1, 1, 1);//magenta color?
    //Renderer* chunkRenderer = new Renderer();
    //chunkEntity->addComponent(chunkRenderer);
    //ChunkSystem* cs = new ChunkSystem();
    //cs->addEntity(chunkEntity);
    //scene->addSystem(cs);
    //rs->addEntity(chunkEntity);

    engine->run();

    //TODO: delete all of the above
}