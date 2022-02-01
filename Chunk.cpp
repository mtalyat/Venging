#include "Chunk.h"

Chunk::Chunk()
{
	//set entire map to empty/air
	int i = 0;
	for (; i < blocks.length(); i++)
	{
		blocks.set(i, 0);
	}
}

VoxelData Chunk::get(const int x, const int y, const int z)
{
	return VoxelData(blocks.get(x, y, z));
}

VoxelData Chunk::get(const int i)
{
	return VoxelData(blocks.get(i));
}

void Chunk::set(const int x, const int y, const int z, int data)
{
	blocks.set(x, y, z, data);
}

void Chunk::set(const int i, int data)
{
	blocks.set(i, data);
}

void Chunk::set(const int x, const int y, const int z, VoxelData vd)
{
	set(x, y, z, vd.getRawData());
}

void Chunk::set(const int i, VoxelData vd)
{
	set(i, vd.getRawData());
}

int Chunk::combineData(BYTE type, BYTE color)
{
	return compact(0, 0, type, color);
}
