#pragma once

#include <cstdbool>
#include "Object.h"
#include "Mesh.h"
#include "Chunk.h"

class ChunkBuilder :
    public Object
{
public:
    /// <summary>
    /// Creates a new ChunkBuilder that will operate on the given Chunk.
    /// </summary>
    /// <param name="chunk"></param>
    ChunkBuilder(Chunk* chunk);

    /// <summary>
    /// Builds Mesh data for the given Mesh, using this ChunkBuilder's Chunk.
    /// </summary>
    /// <param name="mesh"></param>
    /// <returns></returns>
    Mesh* buildMesh(Mesh* mesh);
private:
    //apparently the {} initializes all values to 0 (false)
    bool visitedXN[Chunk::sizeInBlocks]{};
    bool visitedXP[Chunk::sizeInBlocks]{};
    bool visitedYN[Chunk::sizeInBlocks]{};
    bool visitedYP[Chunk::sizeInBlocks]{};
    bool visitedZN[Chunk::sizeInBlocks]{};
    bool visitedZP[Chunk::sizeInBlocks]{};

    Chunk* chunkPtr;
};

