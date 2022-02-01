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
#include "Random.h"

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
    meshEntity->transform()->setPosition(Vector3(-1.0f, -1.0f, -1.0f));

    ////mesh 2
    //Entity* meshEntity2 = new Entity();
    //Renderer* meshRenderer2 = new Renderer();
    //meshEntity2->addComponent(meshRenderer2);
    //rs->addEntity(meshEntity2);
    //meshEntity2->transform()->setParent(meshEntity->transform());
    //meshEntity2->transform()->setLocalPosition(Vector3(0.0f, 1.0f, 0.0f));

    //create a chunk
    Entity* chunkEntity = new Entity();
    Chunk* chunk = new Chunk();
    chunkEntity->addComponent(chunk);
    //chunk->set(1, 1, 1, 1, 1);//magenta color?
    //set random colors
    for (int i = 0; i < 100; i++)
    {
        chunk->set(Random::range(0, Chunk::totalSizeInBlocks), 1, 1);
    }
    Renderer* chunkRenderer = new Renderer();
    chunkEntity->addComponent(chunkRenderer);
    ChunkSystem* cs = new ChunkSystem();
    cs->addEntity(chunkEntity);
    scene->addSystem(cs);
    rs->addEntity(chunkEntity);

    //create a full chunk
    Entity* chunkEntity2 = new Entity();
    chunkEntity2->transform()->setPosition(Vector3(0, 0, Chunk::sizeInBlocks));
    Chunk* chunk2 = new Chunk();
    chunkEntity2->addComponent(chunk2);
    //set all to solid
    for (int i = 0; i < Chunk::totalSizeInBlocks; i++)
    {
        chunk2->set(i, 1, 1);
    }
    Renderer* chunkRenderer2 = new Renderer();
    chunkEntity2->addComponent(chunkRenderer2);
    //add to existing system
    cs->addEntity(chunkEntity2);
    rs->addEntity(chunkEntity2);

    //create striped chunk
    Entity* chunkEntity3 = new Entity();
    chunkEntity3->transform()->setPosition(Vector3(0, 0, Chunk::sizeInBlocks * 2));
    Chunk* chunk3 = new Chunk();
    chunkEntity3->addComponent(chunk3);
    //set to striped
    for (int y = 0; y < Chunk::sizeInBlocks; y++)
    {
        for (int x = 0; x < Chunk::sizeInBlocks; x++)
        {
            for (int z = 0; z < Chunk::sizeInBlocks; z++)
            {
                if (z % 2 == 0 && y % 2 == 0)
                {
                    chunk3->set(x, y, z, 1, 1);
                }
            }
        }
    }
    Renderer* chunkRenderer3 = new Renderer();
    chunkEntity3->addComponent(chunkRenderer3);
    cs->addEntity(chunkEntity3);
    rs->addEntity(chunkEntity3);

    engine->run();

    //TODO: delete all of the above
}