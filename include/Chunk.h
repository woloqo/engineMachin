#ifndef CHUNK_H
#define CHUNK_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<math.h>

#include"../include/Block.h"
#include"../include/MeshBuilder.h"

struct Chunk{
    int chunkId;
    int xPos;
    int yPos;
    int zPos;
    BlockType blocks[16][16][16];

    Chunk();

    void updateMesh(  std::vector<float>& vertices,
                    std::vector<unsigned int>& indices);

                    // Chunk.h
    BlockType getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, BlockType t);
    static bool inBounds(int x, int y, int z){
        return x>=0 && x<16 && y>=0 && y<16 && z>=0 && z<16;
    }
};

#endif