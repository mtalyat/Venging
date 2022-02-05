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

Mesh* ChunkBuilder::buildMesh(Mesh* mesh)
{
    //iterate through each block in the chunk, and check if its face needs drawn
    int x, y, z, i;
    glm::vec3 dir;
    VoxelData vd;

    List<int> vertices;
    List<int> triangles;
    int offset = 0;

    for (x = 0; x < Chunk::sizeInBlocks; x++)
    {
        for (y = 0; y < Chunk::sizeInBlocks; y++)
        {
            for (z = 0; z < Chunk::sizeInBlocks; z++)
            {
                vd = chunkPtr->get(x, y, z);

                if (vd.isEmpty()) continue;

                createRuns(vd.getColor(), x, y, z, &vertices, &triangles, offset);
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

bool ChunkBuilder::visibleFace(const int x, const int y, const int z, const int direction)
{
    glm::vec3 dir = directions[direction];

    int xOff = x + (int)dir.x;
    int yOff = y + (int)dir.y;
    int zOff = z + (int)dir.z;

    if (xOff < 0 || xOff >= Chunk::sizeInBlocks ||
        yOff < 0 || yOff >= Chunk::sizeInBlocks ||
        zOff < 0 || zOff >= Chunk::sizeInBlocks)
    {
        //outside of the chunk
        return true;
    }
    else
    {
        //within the chunk
        //if the adjacent chunk is empty, it is visible
        return chunkPtr->get(xOff, yOff, zOff).isEmpty();
    }
}

void addTriangles(List<int>* triangles, int& offset)
{
    triangles->add(offset + 0); triangles->add(offset + 2); triangles->add(offset + 1);
    triangles->add(offset + 0); triangles->add(offset + 3); triangles->add(offset + 2);

    offset += 4;
}

void createFaceNorth(const int colorId, const int x, const int y, const int z, const int length, List<int>* vertices, List<int>* triangles, int& offset, const int face)
{
    vertices->add(compactVertex(colorId, x + length, y, z + 1, face));
    vertices->add(compactVertex(colorId, x + length, y + 1, z + 1, face));
    vertices->add(compactVertex(colorId, x, y + 1, z + 1, face));
    vertices->add(compactVertex(colorId, x, y, z + 1, face));

    addTriangles(triangles, offset);
}

void createFaceSouth(const int colorId, const int x, const int y, const int z, const int length, List<int>* vertices, List<int>* triangles, int& offset, const int face)
{
    vertices->add(compactVertex(colorId, x, y, z, face));
    vertices->add(compactVertex(colorId, x, y + 1, z, face));
    vertices->add(compactVertex(colorId, x + length, y + 1, z, face));
    vertices->add(compactVertex(colorId, x + length, y, z, face));

    addTriangles(triangles, offset);
}

void createFaceEast(const int colorId, const int x, const int y, const int z, const int length, List<int>* vertices, List<int>* triangles, int& offset, const int face)
{
    vertices->add(compactVertex(colorId, x + 1, y, z, face));
    vertices->add(compactVertex(colorId, x + 1, y + 1, z, face));
    vertices->add(compactVertex(colorId, x + 1, y + 1, z + length, face));
    vertices->add(compactVertex(colorId, x + 1, y, z + length, face));

    addTriangles(triangles, offset);
}

void createFaceWest(const int colorId, const int x, const int y, const int z, const int length, List<int>* vertices, List<int>* triangles, int& offset, const int face)
{
    vertices->add(compactVertex(colorId, x, y, z + length, face));
    vertices->add(compactVertex(colorId, x, y + 1, z + length, face));
    vertices->add(compactVertex(colorId, x, y + 1, z, face));
    vertices->add(compactVertex(colorId, x, y, z, face));

    addTriangles(triangles, offset);
}

void createFaceUp(const int colorId, const int x, const int y, const int z, const int length, List<int>* vertices, List<int>* triangles, int& offset, const int face)
{
    vertices->add(compactVertex(colorId, x, y + 1, z, face));
    vertices->add(compactVertex(colorId, x, y + 1, z + 1, face));
    vertices->add(compactVertex(colorId, x + length, y + 1, z + 1, face));
    vertices->add(compactVertex(colorId, x + length, y + 1, z, face));

    addTriangles(triangles, offset);
}

void createFaceDown(const int colorId, const int x, const int y, const int z, const int length, List<int>* vertices, List<int>* triangles, int& offset, const int face)
{
    vertices->add(compactVertex(colorId, x, y, z + 1, face));
    vertices->add(compactVertex(colorId, x, y, z, face));
    vertices->add(compactVertex(colorId, x + length, y, z, face));
    vertices->add(compactVertex(colorId, x + length, y, z + 1, face));

    addTriangles(triangles, offset);
}

void ChunkBuilder::createRuns(const int colorId, const int x, const int y, const int z, List<int>* vertices, List<int>* triangles, int& offset)
{


    //check all 6 directions to create runs


    //basically, check and make runs so it is sideways rectangles on the X/Z sides, and just rectangles on the Y sides
    //sidways on X/Z so terrains take advantage of this. If it goes up/down, natural terrain will not take advantage of this
    //also make the solid chunk all the same ID just for testing purposes, and maybe some random ones

    int length = 0;
    int startIndex = x + Chunk::sizeInBlocks * (z + Chunk::sizeInBlocks * y);
    //move X by 1 ... += 1
    //move Y by 1 ... += Chunk::sizeInBlocks^2
    //move Z by 1 ... += Chunk::sizeInBlocks
    //basically the same as (1 << 6) since size is 32

    int i;

    if (!visitedWest.get(x, y, z) && visibleFace(x, y, z, (int)Direction::West))
    {
        visitedWest.set(x, y, z, true);
        length = 1;

        //checking west side, but moving north
        for (i = z + 1; i < Chunk::sizeInBlocks; i++)
        {
            if (colorId != chunkPtr->get(x, y, i).getColor())
            {
                break;
            }

            length++;
            visitedWest.set(x, y, i, true);
        }
        
        //make the face
        createFaceWest(colorId, x, y, z, length, vertices, triangles, offset, 2);
    }

    if (!visitedEast.get(x, y, z) && visibleFace(x, y, z, (int)Direction::East))
    {
        visitedEast.set(x, y, z, true);
        length = 1;

        //checking east side, but moving north
        for (i = z + 1; i < Chunk::sizeInBlocks; i++)
        {
            if (colorId != chunkPtr->get(x, y, i).getColor())
            {
                break;
            }

            length++;
            visitedEast.set(x, y, i, true);
        }

        //make the face
        createFaceEast(colorId, x, y, z, length, vertices, triangles, offset, 2);
    }

    if (!visitedNorth.get(x, y, z) && visibleFace(x, y, z, (int)Direction::North))
    {
        visitedNorth.set(x, y, z, true);
        length = 1;

        //checking north side, but moving east
        for (i = x + 1; i < Chunk::sizeInBlocks; i++)
        {
            if (colorId != chunkPtr->get(i, y, z).getColor())
            {
                break;
            }

            length++;
            visitedNorth.set(i, y, z, true);
        }

        //make the face
        createFaceNorth(colorId, x, y, z, length, vertices, triangles, offset, 1);
    }

    if (!visitedSouth.get(x, y, z) && visibleFace(x, y, z, (int)Direction::South))
    {
        visitedSouth.set(x, y, z, true);
        length = 1;

        //checking south side, but moving east
        for (i = x + 1; i < Chunk::sizeInBlocks; i++)
        {
            if (colorId != chunkPtr->get(i, y, z).getColor())
            {
                break;
            }

            length++;
            visitedSouth.set(i, y, z, true);
        }

        //make the face
        createFaceSouth(colorId, x, y, z, length, vertices, triangles, offset, 1);
    }

    if (!visitedUp.get(x, y, z) && visibleFace(x, y, z, (int)Direction::Up))
    {
        visitedUp.set(x, y, z, true);
        length = 1;

        //checking top side, but moving east
        for (i = x + 1; i < Chunk::sizeInBlocks; i++)
        {
            if (colorId != chunkPtr->get(i, y, z).getColor())
            {
                break;
            }

            length++;
            visitedUp.set(i, y, z, true);
        }

        //make the face
        createFaceUp(colorId, x, y, z, length, vertices, triangles, offset, 0);
    }

    if (!visitedDown.get(x, y, z) && visibleFace(x, y, z, (int)Direction::Down))
    {
        visitedDown.set(x, y, z, true);
        length = 1;

        //checking bottom side, but moving east
        for (i = x + 1; i < Chunk::sizeInBlocks; i++)
        {
            if (colorId != chunkPtr->get(i, y, z).getColor())
            {
                break;
            }

            length++;
            visitedDown.set(i, y, z, true);
        }

        //make the face
        createFaceDown(colorId, x, y, z, length, vertices, triangles, offset, 3);
    }
}