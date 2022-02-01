#include "ChunkSystem.h"

/*

    Note: Random 100 is not valid for statistics, as it is possible for blocks to replace another during generation,
    thus making it render less than 100 blocks.

    Benchmark 1 for mesh building: No optimizations
    100% of original

Random 100:         9568 verts, 3588 tris
Solid:              98304 verts, 36864 tris
Stripes X dir:      532480 verts, 199680 tris
Stripes Y dir:      532480 verts, 199680 tris
Stripes Z dir:      532480 verts, 199680 tris

    Benchmark 2 for mesh building: Compacted vertices
    25% of original

Random 100:         2368 verts, 3552 triangles
Solid:              24576 verts, 36864 tris
Stripes X dir:      133120 verts, 199680 tris
Stripes Y dir:      133120 verts, 199680 tris
Stripes Z dir:      133120 verts, 199680 tris

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

unsigned int compactVertex(const unsigned int colorIndex, const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int faceShade)
{
    unsigned int i = colorIndex;

    i <<= 6;
    i |= x;

    i <<= 6;
    i |= y;

    i <<= 6;
    i |= z;

    i <<= 2;
    i |= faceShade;

    //shift over so it is all left aligned
    i <<= 4;

    return i;
}

void createTopFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(compactVertex(colorIndex, x, y + 1, z, 0));
    vertices->add(compactVertex(colorIndex, x + 1, y + 1, z, 0));
    vertices->add(compactVertex(colorIndex, x + 1, y + 1, z + 1, 0));
    vertices->add(compactVertex(colorIndex, x, y + 1, z + 1, 0));

    triangles->add(offset + 0); triangles->add(offset + 1); triangles->add(offset + 2);
    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 3);

    offset += 4;
}

void createBottomFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(compactVertex(colorIndex, x, y, z, 3));
    vertices->add(compactVertex(colorIndex, x + 1, y, z, 3));
    vertices->add(compactVertex(colorIndex, x + 1, y, z + 1, 3));
    vertices->add(compactVertex(colorIndex, x, y, z + 1, 3));

    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 1);
    triangles->add(offset + 0); triangles->add(offset + 3); triangles->add(offset + 2);

    offset += 4;
}

void createNorthFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(compactVertex(colorIndex, x + 1, y, z + 1, 1));
    vertices->add(compactVertex(colorIndex, x + 1, y + 1, z + 1, 1));
    vertices->add(compactVertex(colorIndex, x, y + 1, z + 1, 1));
    vertices->add(compactVertex(colorIndex, x, y, z + 1, 1));

    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 1);
    triangles->add(offset + 0); triangles->add(offset + 3); triangles->add(offset + 2);

    offset += 4;
}

void createSouthFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(compactVertex(colorIndex, x, y, z, 1));
    vertices->add(compactVertex(colorIndex, x, y + 1, z, 1));
    vertices->add(compactVertex(colorIndex, x + 1, y + 1, z, 1));
    vertices->add(compactVertex(colorIndex, x + 1, y, z, 1));

    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 1);
    triangles->add(offset + 0); triangles->add(offset + 3); triangles->add(offset + 2);

    offset += 4;
}

void createEastFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(compactVertex(colorIndex, x + 1, y, z, 2));
    vertices->add(compactVertex(colorIndex, x + 1, y + 1, z, 2));
    vertices->add(compactVertex(colorIndex, x + 1, y + 1, z + 1, 2));
    vertices->add(compactVertex(colorIndex, x + 1, y, z + 1, 2));

    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 1);
    triangles->add(offset + 0); triangles->add(offset + 3); triangles->add(offset + 2);

    offset += 4;
}

void createWestFace(List<int>* vertices, int& offset, List<int>* triangles, const int x, const int y, const int z, const unsigned int colorIndex)
{
    vertices->add(compactVertex(colorIndex, x, y, z + 1, 2));
    vertices->add(compactVertex(colorIndex, x, y + 1, z + 1, 2));
    vertices->add(compactVertex(colorIndex, x, y + 1, z, 2));
    vertices->add(compactVertex(colorIndex, x, y, z, 2));

    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 1);
    triangles->add(offset + 0); triangles->add(offset + 3); triangles->add(offset + 2);

    offset += 4;
}

void createRun(List<int>* vertices, int& offset, List<int>* triangles, int x, int y, int z, const int xDir, const int yDir, const int zDir, const int xCh, const int yCh, const int zCh, const unsigned int colorIndex)
{
    while (x < Chunk::sizeInBlocks && z < Chunk::sizeInBlocks && y < Chunk::sizeInBlocks)
    {

    }
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

    Console::Log("[LOG] Built ChunkSystem Mesh with %s vertices and %s triangles indices.\n", std::to_string(vertices.length()).c_str(), std::to_string(triangles.length()).c_str());

    //add it to the mesh
    if (vertices.length() > 0)
    {
        mesh->setVertices(vertices.getPointerToFirst(), vertices.length());
        mesh->setTriangles(triangles.getPointerToFirst(), triangles.length());
        mesh->rebuild();
    }
}

