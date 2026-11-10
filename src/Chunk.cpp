#include "../include/Chunk.h"

Chunk::Chunk(){
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                this->blocks[x][y][z] = GRASS;
            }
        }
    }
}

void Chunk::updateMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices){
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                addCube(vertices, indices, glm::ivec3(x,y,z), this->blocks[x][y][z]);
            }
        }
    }
}
