#ifndef BLOCK_H
#define BLOCK_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<math.h>

enum Face : uint8_t{
    TOP, 
    BOTTOM, 
    NORTH, 
    SOUTH, 
    EAST, 
    WEST,
    FACE_COUNT
};
enum BlockType : uint8_t{
    GRASS,
    BLOCK_TYPE_COUNT
};

struct BlockInfo{
    int tiles[FACE_COUNT];
    bool solid;
};

const BlockInfo& getBlockInfo(BlockType type);
int  getTile(BlockType type, Face face);
bool isSolid(BlockType type);

#endif