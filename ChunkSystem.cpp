#include "ChunkSystem.h"

/*

Benchmark 1 for mesh building:

Random 100:         9568 verts, 3588 tris
Solid:              98304 verts, 36864 tris
Stripes X dir:      532480 verts, 199680 tris
Stripes Y dir:      532480 verts, 199680 tris
Stripes Z dir:      532480 verts, 199680 tris

*/

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

void createTopFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    //also gotta add colors
    vertices->add(x); vertices->add(y + 1); vertices->add(z); vertices->add(colorIndex);           //  0
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z); vertices->add(colorIndex);       //  1
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z + 1); vertices->add(colorIndex);   //  2
    vertices->add(x); vertices->add(y + 1); vertices->add(z + 1); vertices->add(colorIndex);       //  3

    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 1);
    triangles->add(offset + 0); triangles->add(offset + 3); triangles->add(offset + 2);

    offset += 4;
}

void createBottomFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(x); vertices->add(y); vertices->add(z); vertices->add(colorIndex);           //  0
    vertices->add(x + 1); vertices->add(y); vertices->add(z); vertices->add(colorIndex);       //  1
    vertices->add(x + 1); vertices->add(y); vertices->add(z + 1); vertices->add(colorIndex);   //  2
    vertices->add(x); vertices->add(y); vertices->add(z + 1); vertices->add(colorIndex);       //  3

    triangles->add(offset + 0); triangles->add(offset + 1); triangles->add(offset + 2);
    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 3);

    offset += 4;
}

void createNorthFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(x + 1); vertices->add(y); vertices->add(z + 1); vertices->add(colorIndex);           //  0
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z + 1); vertices->add(colorIndex);       //  1
    vertices->add(x); vertices->add(y + 1); vertices->add(z + 1); vertices->add(colorIndex);           //  2
    vertices->add(x); vertices->add(y); vertices->add(z + 1); vertices->add(colorIndex);               //  3

    triangles->add(offset + 0); triangles->add(offset + 1); triangles->add(offset + 2);
    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 3);

    offset += 4;
}

void createSouthFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(x); vertices->add(y); vertices->add(z); vertices->add(colorIndex);                   //  0
    vertices->add(x); vertices->add(y + 1); vertices->add(z); vertices->add(colorIndex);               //  1
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z); vertices->add(colorIndex);           //  2
    vertices->add(x + 1); vertices->add(y); vertices->add(z); vertices->add(colorIndex);               //  3

    triangles->add(offset + 0); triangles->add(offset + 1); triangles->add(offset + 2);
    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 3);

    offset += 4;
}

void createEastFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(x + 1); vertices->add(y); vertices->add(z); vertices->add(colorIndex);                   //  0
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z); vertices->add(colorIndex);               //  1
    vertices->add(x + 1); vertices->add(y + 1); vertices->add(z + 1); vertices->add(colorIndex);           //  2
    vertices->add(x + 1); vertices->add(y); vertices->add(z + 1); vertices->add(colorIndex);               //  3

    triangles->add(offset + 0); triangles->add(offset + 1); triangles->add(offset + 2);
    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 3);

    offset += 4;
}

void createWestFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(x); vertices->add(y); vertices->add(z + 1); vertices->add(colorIndex);                   //  0
    vertices->add(x); vertices->add(y + 1); vertices->add(z + 1); vertices->add(colorIndex);               //  1
    vertices->add(x); vertices->add(y + 1); vertices->add(z); vertices->add(colorIndex);                   //  2
    vertices->add(x); vertices->add(y); vertices->add(z); vertices->add(colorIndex);;                      //  3

    triangles->add(offset + 0); triangles->add(offset + 1); triangles->add(offset + 2);
    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 3);

    offset += 4;
}

void ChunkSystem::buildMesh(Chunk* chunk)
{
    //no point in building if no renderer
    Renderer* r = chunk->entity()->getComponent<Renderer>();
    Mesh* mesh = r->createNewMesh();

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
    int offset = 0;

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
                        switch (i)
                        {
                        case 0:
                            createTopFace(&vertices, offset, &triangles, x, y, z, chunk->get(x, y, z).getColor());
                            break;
                        case 1:
                            createBottomFace(&vertices, offset, &triangles, x, y, z, chunk->get(x, y, z).getColor());
                            break;
                        case 2:
                            createNorthFace(&vertices, offset, &triangles, x, y, z, chunk->get(x, y, z).getColor());
                            break;
                        case 3:
                            createSouthFace(&vertices, offset, &triangles, x, y, z, chunk->get(x, y, z).getColor());
                            break;
                        case 4:
                            createEastFace(&vertices, offset, &triangles, x, y, z, chunk->get(x, y, z).getColor());
                            break;
                        case 5:
                            createWestFace(&vertices, offset, &triangles, x, y, z, chunk->get(x, y, z).getColor());
                            break;
                        }
                    }
                }
            }
        }
    }

    Console::Log("Built ChunkSystem Mesh with %s vertices and %s triangles indices.\n", std::to_string(vertices.length()).c_str(), std::to_string(triangles.length()).c_str());

    //add it to the mesh
    if (vertices.length() > 0)
    {
        mesh->setVertices(vertices.getPointerToFirst(), vertices.length());
        mesh->setTriangles(triangles.getPointerToFirst(), triangles.length());
        mesh->rebuild();
    }
}

