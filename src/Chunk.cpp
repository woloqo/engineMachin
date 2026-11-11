#include "../include/Chunk.h"

Chunk::Chunk(int id, glm::ivec3 pos){
    this->id = id;
    this->pos = pos;
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

Chunk::Chunk(){

}

/*
Chunk::Chunk(){
    const float cx = 7.5f, cy = 7.5f, cz = 7.5f; 
    const float radius = 8.0f;                   

    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                float dx = x - cx;
                float dy = y - cy;
                float dz = z - cz;
                float distSq = dx*dx + dy*dy + dz*dz;

                if(distSq <= radius * radius){
                    if(y <= 8) this->blocks[x][y][z] = DIRT;
                    else if(y <= 15 && y >= 9) this->blocks[x][y][z] = GRASS;
                } else {
                    this->blocks[x][y][z] = AIR;
                }
            }
        }
    }
}
*/

BlockType Chunk::getBlock(int x, int y, int z) const {
    if(!inBounds(x,y,z)) return AIR;
    return blocks[x][y][z];
}
void Chunk::setBlock(int x, int y, int z, BlockType t){
    if(inBounds(x,y,z)) blocks[x][y][z] = t;
}

void Chunk::updateMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices){
    for(int x=0;x<16;x++) for(int y=0;y<16;y++) for(int z=0;z<16;z++){
        if(blocks[x][y][z] == AIR) continue;
        bool faces[6] = {
            getBlock(x,y+1,z) == AIR, // top
            getBlock(x,y-1,z) == AIR, // bottom
            getBlock(x,y,z-1) == AIR, // north
            getBlock(x,y,z+1) == AIR, // south
            getBlock(x+1,y,z) == AIR, // east
            getBlock(x-1,y,z) == AIR  // west
        };
        addCube(vertices, indices, glm::ivec3(x + this->pos.x, y + this->pos.y, z + this->pos.z), blocks[x][y][z], faces);
    }
}