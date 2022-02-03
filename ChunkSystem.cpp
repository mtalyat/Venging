#include "ChunkSystem.h"

/*

    Benchmark 1 for mesh building: No optimizations
    100% of original

Solid:              98304 verts, 36864 tris
Stripes X dir:      532480 verts, 199680 tris
Stripes Y dir:      532480 verts, 199680 tris
Stripes Z dir:      532480 verts, 199680 tris

    Benchmark 2 for mesh building: Compacted vertices
    75% improvement for vertex count, 0% improvement for triangles and time

Solid:              24576 verts, 36864 tris, 0.03 seconds
Stripes X dir:      133120 verts, 199680 tris, 0.06 seconds
Stripes Y dir:      133120 verts, 199680 tris, 0.06 seconds
Stripes Z dir:      133120 verts, 199680 tris, 0.06 seconds

    Benchmark 3 for mesh building: Run meshing

Solid:              780 verts       (3.2% of prev, 0.7% of orig),   1170 tris       (3.2%),     0.015 seconds   (50.0% of prev)
Stripes X dir:      6144 verts      (4.6% of prev, 1.2% of orig),   9216 tris,      (4.6%),     0.009 seconds   (15.0% of prev)
Stripes Y dir:      69632 verts     (52.3% of prev, 13.1% of orig), 104448 tris,    (52.3%),    0.025 seconds   (41.7% of prev)
Stripes Z dir:      133120 verts    (100% of prev, 25% of orig),    199680 tris,    (100.0%),   0.04 seconds    (66.7% of prev)

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

