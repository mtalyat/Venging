#pragma once

#include <cstdbool>
#include <glm/glm.hpp>
#include "Object.h"
#include "Mesh.h"
#include "Chunk.h"
#include "Direction.h"
#include "Map.h"

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
    Map<bool> visitedWest = Map<bool>(Chunk::sizeInBlocks);//initialize to false
    Map<bool> visitedEast = Map<bool>(Chunk::sizeInBlocks);
    Map<bool> visitedNorth = Map<bool>(Chunk::sizeInBlocks);
    Map<bool> visitedSouth = Map<bool>(Chunk::sizeInBlocks);
    Map<bool> visitedUp = Map<bool>(Chunk::sizeInBlocks);
    Map<bool> visitedDown = Map<bool>(Chunk::sizeInBlocks);

    Chunk* chunkPtr;

    const glm::vec3 directions[6] = {
        glm::vec3(0, 1, 0),
        glm::vec3(0, -1, 0),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, -1),
        glm::vec3(1, 0, 0),
        glm::vec3(-1, 0, 0)
    };

    bool visibleFace(const int x, const int y, const int z, const int direction);
    void createRuns(const int colorId, const int x, const int y, const int z, List<int>* vertices, List<int>* triangles, int& offset);
};

