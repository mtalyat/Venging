#include "Engine.h"
#include "Scene.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "Window.h"
#include "Console.h"
#include "TransformComponent.h"
#include "Chunk.h"
#include "RenderingSystem.h"
#include "ChunkSystem.h"
#include "Random.h"

int main()
{
    //setup engine
    Window* window = new Window(800, 800, "Test");
    window->setBackgroundColor(Color::gray());

    Input::createActionMap("default");

    Engine* engine = new Engine(window);
    Scene* scene = new Scene();
    engine->addScene(scene);

    Entity* camEntity = new Entity();
    camEntity->transform()->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
    CameraComponent* cam = new CameraComponent();
    camEntity->addComponent(cam);

    //rendering
    RenderingSystem* rs = new RenderingSystem();
    scene->addSystem(rs);

    //create a chunk
    Entity* chunkEntity = new Entity();
    Chunk* chunk = new Chunk();
    chunkEntity->addComponent(chunk);
    //chunk->set(1, 1, 1, 1, 1);//magenta color?
    //set random colors
    for (int i = 0; i < 100; i++)
    {
        chunk->set(Random::range(0, Chunk::totalSizeInBlocks), VoxelData(1, Random::range(0, 256)));
    }
    RendererComponent* chunkRenderer = new RendererComponent();
    chunkEntity->addComponent(chunkRenderer);
    ChunkSystem* cs = new ChunkSystem();
    cs->addEntity(chunkEntity);
    scene->addSystem(cs);
    rs->addEntity(chunkEntity);

    //create a full chunk
    Entity* chunkEntity2 = new Entity();
    chunkEntity2->transform()->setPosition(glm::vec3(0, 0, Chunk::sizeInBlocks));
    Chunk* chunk2 = new Chunk();
    chunkEntity2->addComponent(chunk2);
    //set all to solid
    for (int i = 0; i < Chunk::totalSizeInBlocks; i++)
    {
        if (i <= 1)
        {
            chunk2->set(i, VoxelData(0, 0));
        }
        else
        if (Random::range(0, 20) != -1)
        {
            chunk2->set(i, VoxelData(1, 231));//white
        }
        else
        {
            chunk2->set(i, VoxelData(1, 9));//red
        }
        
    }
    RendererComponent* chunkRenderer2 = new RendererComponent();
    chunkEntity2->addComponent(chunkRenderer2);
    //add to existing system
    cs->addEntity(chunkEntity2);
    rs->addEntity(chunkEntity2);

    //create striped chunk
    Entity* chunkEntity3 = new Entity();
    chunkEntity3->transform()->setPosition(glm::vec3(0, 0, Chunk::sizeInBlocks * 2));
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
                    chunk3->set(x, y, z, VoxelData(1, 1));
                }
            }
        }
    }
    RendererComponent* chunkRenderer3 = new RendererComponent();
    chunkEntity3->addComponent(chunkRenderer3);
    cs->addEntity(chunkEntity3);
    rs->addEntity(chunkEntity3);

    //create striped chunk going the other way
    Entity* chunkEntity4 = new Entity();
    chunkEntity4->transform()->setPosition(glm::vec3(0, 0, Chunk::sizeInBlocks * 3));
    Chunk* chunk4 = new Chunk();
    chunkEntity4->addComponent(chunk4);
    //set to striped
    for (int y = 0; y < Chunk::sizeInBlocks; y++)
    {
        for (int x = 0; x < Chunk::sizeInBlocks; x++)
        {
            for (int z = 0; z < Chunk::sizeInBlocks; z++)
            {
                if (x % 2 == 0 && y % 2 == 0)
                {
                    chunk4->set(x, y, z, VoxelData(1, 2));
                }
            }
        }
    }
    RendererComponent* chunkRenderer4 = new RendererComponent();
    chunkEntity4->addComponent(chunkRenderer4);
    cs->addEntity(chunkEntity4);
    rs->addEntity(chunkEntity4);

    //create striped chunk going up/down
    Entity* chunkEntity5 = new Entity();
    chunkEntity5->transform()->setPosition(glm::vec3(0, 0, Chunk::sizeInBlocks * 4));
    Chunk* chunk5 = new Chunk();
    chunkEntity5->addComponent(chunk5);
    //set to striped
    for (int y = 0; y < Chunk::sizeInBlocks; y++)
    {
        for (int x = 0; x < Chunk::sizeInBlocks; x++)
        {
            for (int z = 0; z < Chunk::sizeInBlocks; z++)
            {
                if (x % 2 == 0 && z % 2 == 0)
                {
                    chunk5->set(x, y, z, VoxelData(1, 4));
                }
            }
        }
    }
    RendererComponent* chunkRenderer5 = new RendererComponent();
    chunkEntity5->addComponent(chunkRenderer5);
    cs->addEntity(chunkEntity5);
    rs->addEntity(chunkEntity5);

    engine->run();

    //TODO: delete all of the above
}