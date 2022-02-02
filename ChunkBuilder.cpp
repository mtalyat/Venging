#include "ChunkBuilder.h"

ChunkBuilder::ChunkBuilder(Chunk* chunk)
{
	chunkPtr = chunk;
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

Mesh* ChunkBuilder::buildMesh(Mesh* mesh)
{
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
                    if (shouldCreateFace(chunkPtr, x, y, z, dir.x, dir.y, dir.z))
                    {
                        //we should create the face
                        switch (i)
                        {
                        case 0:
                            createTopFace(&vertices, offset, &triangles, x, y, z, chunkPtr->get(x, y, z).getColor());
                            break;
                        case 1:
                            createBottomFace(&vertices, offset, &triangles, x, y, z, chunkPtr->get(x, y, z).getColor());
                            break;
                        case 2:
                            createNorthFace(&vertices, offset, &triangles, x, y, z, chunkPtr->get(x, y, z).getColor());
                            break;
                        case 3:
                            createSouthFace(&vertices, offset, &triangles, x, y, z, chunkPtr->get(x, y, z).getColor());
                            break;
                        case 4:
                            createEastFace(&vertices, offset, &triangles, x, y, z, chunkPtr->get(x, y, z).getColor());
                            break;
                        case 5:
                            createWestFace(&vertices, offset, &triangles, x, y, z, chunkPtr->get(x, y, z).getColor());
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

	return mesh;
}
