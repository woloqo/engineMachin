#include "../include/Chunk.h"

Chunk::Chunk(){
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                if(y <= 12) this->blocks[x][y][z] = STONE;
                if(y <= 14 && y >= 13) this->blocks[x][y][z] = DIRT;
                if(y == 15) this->blocks[x][y][z] = GRASS;
            }
        }
    }
}

void Chunk::updateMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices){
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                glm::ivec3 pos = glm::ivec3(x,y,z);
                bool faces[6] = {1, 1, 1, 1, 1, 1};
                //orden TOP, BOTTOM, NORTH, SOUTH, EAST, WEST
                //      y+1    y-1    z-1    z+1   x+1   x-1
                if(y < 15) faces[0] = this->blocks[x][y+1][z] == AIR ? 1 : 0; //top
                if(y > 0 ) faces[1] = this->blocks[x][y-1][z] == AIR ? 1 : 0; //bottom
                if(z > 0 ) faces[2] = this->blocks[x][y][z-1] == AIR ? 1 : 0; //north
                if(z < 15) faces[3] = this->blocks[x][y][z+1] == AIR ? 1 : 0; //south
                if(x < 15) faces[4] = this->blocks[x+1][y][z] == AIR ? 1 : 0; //east
                if(x > 0 ) faces[5] = this->blocks[x-1][y][z] == AIR ? 1 : 0; //west
                addCube(vertices, indices, glm::ivec3(x,y,z), this->blocks[x][y][z], faces);
            }
        }
    }
}
