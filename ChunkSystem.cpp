#include "ChunkSystem.h"

void ChunkSystem::init()
{
    //build meshes
    int i = 0;
    for (; i < chunks.length(); i++)
    {
        buildMesh(chunks[i]);
    }
}

void ChunkSystem::addEntity(Entity* entity)
{
    Chunk* c = entity->getComponent<Chunk>();

    if (c == NULL)
    {
        Console::LogWarning("The given Entity did not have an attached Chunk Component.");
        return;
    }

    entities.add(entity);
    chunks.add(c);
}

bool ChunkSystem::removeEntity(Entity* entity)
{
    return false;
}

bool shouldCreateFace(Chunk* chunk, int x, int y, int z, int xDir, int yDir, int zDir)
{
    //if this block is air, do nothing
    if (chunk->get(x, y, z).getType() == VoxelType::Air)
    {
        return false;
    }

    //only visible at this point

    //check if out of the chunk
    //if so, create
    if (x + xDir < 0 || x + xDir >= Chunk::sizeInBlocks ||
        y + yDir < 0 || y + yDir >= Chunk::sizeInBlocks ||
        z + zDir < 0 || z + zDir >= Chunk::sizeInBlocks)
    {
        return true;
    }

    //not air, must be solid
    //only draw face if the adjacent block is air
    return chunk->get(x + xDir, y + yDir, z + zDir).getType() == VoxelType::Air;
}

void createTopFace(List<int>* vertices, List<int>* triangles, const int x, const int y, const int z)
{
    vertices->add(x); vertices->add(y + 1); vertices->add(z);
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z);
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z + 1);
    vertices->add(x); vertices->add(y + 1); vertices->add(z + 1);

    triangles->add(0); triangles->add(1); triangles->add(2);
    triangles->add(0); triangles->add(2); triangles->add(3);
}

void createBottomFace(List<int>* vertices, List<int>* triangles, const int x, const int y, const int z)
{

}

void createFrontFace(List<int>* vertices, List<int>* triangles, const int x, const int y, const int z)
{

}

void createBackFace(List<int>* vertices, List<int>* triangles, const int x, const int y, const int z)
{

}

void createLeftFace(List<int>* vertices, List<int>* triangles, const int x, const int y, const int z)
{

}

void createRightFace(List<int>* vertices, List<int>* triangles, const int x, const int y, const int z)
{

}

void ChunkSystem::buildMesh(Chunk* chunk)
{
    Console::Log("Building mesh");

    //no point in building if no renderer
    Renderer* r = chunk->entity()->getComponent<Renderer>();
    Mesh* mesh = r->mesh();

    if (r == NULL)
    {
        Console::LogWarning("The given Chunk did not have an attached Renderer Component when building the Mesh.");
        return;
    }

    //build the mesh
    //iterate through each block in the chunk, and check if its face needs drawn
    int x, y, z, i;
    Vector3 dir;

    const Vector3 directions[6] = {
        Vector3(0, 1, 0),
        Vector3(0, -1, 0),
        Vector3(0, 0, 1),
        Vector3(0, 0, -1),
        Vector3(1, 0, 0),
        Vector3(-1, 0, 0)
    };

    List<int> vertices;
    List<int> triangles;

    //generate each face
    for (x = 0; x < Chunk::sizeInBlocks; x++)
    {
        for (z = 0; z < Chunk::sizeInBlocks; z++)
        {
            for (y = 0; y < Chunk::sizeInBlocks; y++)
            {
                for (i = 0; i < 6; i++)
                {
                    dir = directions[i];
                    if (shouldCreateFace(chunk, x, y, z, dir.x, dir.y, dir.z))
                    {
                        //we should create the face
                        Console::Log("Creating face at %s facing %s.\n", Vector3((float)x, (float)y, (float)z).toString().c_str(), dir.toString().c_str());
                        switch (i)
                        {
                        case 0:
                            createTopFace(&vertices, &triangles, x, y, z);
                        }
                    }
                }
            }
        }
    }

    //add it to the mesh
    if (vertices.length() > 0)
    {
        mesh->setVertices(vertices.getPointerToFirst(), vertices.length());
        mesh->setTriangles(triangles.getPointerToFirst(), triangles.length());
    }
}
