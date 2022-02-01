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

	/// <summary>
	/// Gets the corresponding VoxelData at the given position.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <returns></returns>
	VoxelData get(const int x, const int y, const int z);
	/// <summary>
	/// Gets the corresponding VoxelData at the given index.
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	VoxelData get(const int i);

	/// <summary>
	/// Sets the corresponding data at the given position.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="data"></param>
	void set(const int x, const int y, const int z, int data);
	/// <summary>
	/// Sets the corresponding data at the given index.
	/// </summary>
	/// <param name="i"></param>
	/// <param name="data"></param>
	void set(const int i, int data);

	/// <summary>
	/// Sets the corresponding VoxelData at the given position.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <param name="vd"></param>
	void set(const int x, const int y, const int z, VoxelData vd);
	/// <summary>
	/// Gets the corresponding VoxelData at the given index.
	/// </summary>
	/// <param name="i"></param>
	/// <param name="vd"></param>
	void set(const int i, VoxelData vd);

	static const int sizeInBlocks = 32;
	static const int totalSizeInBlocks = sizeInBlocks * sizeInBlocks * sizeInBlocks;
private:
	Map<int> blocks = Map<int>(sizeInBlocks);

	int combineData(BYTE type, BYTE color);
};

#endif