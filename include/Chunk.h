#ifndef CHUNK_H
#define CHUNK_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<math.h>

#include"Block.h"
#include"MeshBuilder.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

const int CHUNK_SIZE    = 16;
const int CHUNK_HEIGHT  = 128;

class World;

struct Chunk{

    int id;
    glm::ivec2 worldPos;
    glm::ivec3 localPos;
    BlockType blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

    VAO vao;
    VBO vbo;
    EBO ebo;
    GLsizei indexCount = 0;
    bool meshCreated = false;
    bool dirty = true;

    Chunk(glm::ivec2 worldPos);

    //void updateMesh(  std::vector<float>& vertices,
    //                std::vector<unsigned int>& indices);
    void generate();
    void updateMesh(const World& world);
    void draw();


                    // Chunk.h
    BlockType getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, BlockType t);
    static bool inBounds(int x, int y, int z){
        return x>=0 && x<CHUNK_SIZE && y>=0 && y<CHUNK_HEIGHT && z>=0 && z<CHUNK_SIZE;
    }
};

#endif