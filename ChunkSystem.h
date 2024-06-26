#ifndef CHUNKSYSTEM_H
#define CHUNKSYSTEM_H

#include "System.h"
#include "Chunk.h"
#include "RendererComponent.h"
#include "Console.h"
#include "Vector3.h"
#include "Color.h"
#include "Stopwatch.h"
#include "ChunkBuilder.h"

class ChunkSystem :
    public System
{
public:
    void init() override;

    void addEntity(Entity* entity) override;
    bool removeEntity(Entity* entity) override;

private:
    List<Chunk*> chunks;

    /// <summary>
    /// Builds the Mesh of this ChunkSystem to reflect the data within the given Chunk.
    /// </summary>
    /// <param name="chunk"></param>
    void buildMesh(Chunk* chunk);
};

#endif
