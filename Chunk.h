#ifndef CHUNK_H
#define CHUNK_H

#include "Component.h"
#include "Map.h"
#include "Helper.h"
#include "VoxelData.h"

class Chunk
	: public Component
{
public:
	Chunk();

	VoxelData get(const int x, const int y, const int z);
	VoxelData get(const int i);

	void set(const int x, const int y, const int z, int data);
	void set(const int i, int data);

	void set(const int x, const int y, const int z, VoxelData vd);
	void set(const int i, VoxelData vd);

	void set(const int x, const int y, const int z, BYTE type, BYTE color);
	void set(const int i, BYTE type, BYTE color);

	static const int sizeInBlocks = 64;
private:
	Map<int> blocks = Map<int>(sizeInBlocks);

	int combineData(BYTE type, BYTE color);
};

#endif