#ifndef VOXELDATA_H
#define VOXELDATA_H

#include "Object.h"
#include "Helper.h"
#include "VoxelType.h"

struct VoxelData :
    public Object
{
public:
    VoxelData(int data);
    VoxelData(int type, int color);

    VoxelType getType();
    int getRawType();
    int getColor();
    int getRawData();

    std::string toString() override;
private:
    int data;
};

#endif
