#include "VoxelData.h"

VoxelData::VoxelData()
{
    this->data = 0;
}

VoxelData::VoxelData(int data)
{
    this->data = data;
}

VoxelData::VoxelData(int type, int color)
{
    data = compact(0, 0, type, color);
}

VoxelType VoxelData::getType()
{
    return (VoxelType)getRawType();
}

int VoxelData::getRawType()
{
    return extract(data, 2);;
}

int VoxelData::getColor()
{
    return extract(data, 3);
}

int VoxelData::getRawData()
{
    return data;
}

bool VoxelData::isEmpty()
{
    return getRawType() == 0;
}

std::string VoxelData::toString()
{
    return std::string();
}
