#ifndef VOXELDATA_H
#define VOXELDATA_H

#include "Object.h"
#include "Helper.h"
#include "VoxelType.h"

struct VoxelData :
    public Object
{
public:
    /// <summary>
    /// Creates a new VoxelData using the raw data value.
    /// </summary>
    /// <param name="data"></param>
    VoxelData(int data);
    /// <summary>
    /// Creates a new VoxelData using the given type and color index.
    /// </summary>
    /// <param name="type"></param>
    /// <param name="color"></param>
    VoxelData(int type, int color);

    /// <summary>
    /// Gets the VoxelType stored in this VoxelData.
    /// </summary>
    /// <returns></returns>
    VoxelType getType();
    /// <summary>
    /// Gets the raw VoxelType integer.
    /// </summary>
    /// <returns></returns>
    int getRawType();
    /// <summary>
    /// Gets the color index stored in this VoxelData.
    /// </summary>
    /// <returns></returns>
    int getColor();
    /// <summary>
    /// Gets the raw data stored in this VoxelData.
    /// </summary>
    /// <returns></returns>
    int getRawData();

    std::string toString() override;
private:
    int data;
};

#endif
