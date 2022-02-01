#ifndef CHUNKSYSTEM_H
#define CHUNKSYSTEM_H

#include "System.h"
#include "Chunk.h"
#include "Renderer.h"
#include "Console.h"
#include "Vector3.h"
#include "Color.h"

class ChunkSystem :
    public System
{
public:
    void init() override;

    void addEntity(Entity* entity) override;
    bool removeEntity(Entity* entity) override;

private:
    List<Chunk*> chunks;

    void buildMesh(Chunk* chunk);
};

#endif
