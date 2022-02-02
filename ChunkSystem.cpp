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
    75% improvement for vertex count, 0% improvement for triangles and time

Random 100:         2368 verts, 3552 tris, 0.01 seconds
Solid:              24576 verts, 36864 tris, 0.03 seconds
Stripes X dir:      133120 verts, 199680 tris, 0.06 seconds
Stripes Y dir:      133120 verts, 199680 tris, 0.06 seconds
Stripes Z dir:      133120 verts, 199680 tris, 0.06 seconds

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

void ChunkSystem::buildMesh(Chunk* chunk)
{
    Stopwatch watch;
    watch.start();

    //no point in building if no renderer
    Renderer* r = chunk->entity()->getComponent<Renderer>();
    Mesh* mesh = r->createNewMesh();

    if (r == NULL)
    {
        Console::LogWarning("The given Chunk did not have an attached Renderer Component when building the Mesh.");
        return;
    }

    //build the mesh
    ChunkBuilder cb(chunk);
    cb.buildMesh(mesh);

    watch.stop();

    Console::Log("[LOG] Built ChunkSystem Mesh in %s seconds.\n", std::to_string(watch.getTotalTimeElapsed()).c_str());
}

