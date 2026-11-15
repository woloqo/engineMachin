#include "../include/Chunk.h"
#include "../include/World.h"

Chunk::Chunk(glm::ivec2 coord){
    this->worldPos  = coord;
    this->localPos  = glm::ivec3(coord.x * CHUNK_SIZE, 0, coord.y * CHUNK_SIZE);
    generate();
}

void Chunk::generate(){
    for(int x = 0; x < CHUNK_SIZE; x++)
        for(int y = 0; y < CHUNK_HEIGHT; y++)
            for(int z = 0; z < CHUNK_SIZE; z++){
                if(y <= 12)      blocks[x][y][z] = STONE;
                else if(y <= 14) blocks[x][y][z] = DIRT;
                else if(y == 15) blocks[x][y][z] = GRASS;
                else             blocks[x][y][z] = AIR;
            }
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

/*
void Chunk::updateMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices){
    for(int x=0;x<CHUNK_SIZE;x++) for(int y=0;y<CHUNK_HEIGHT;y++) for(int z=0;z<CHUNK_SIZE;z++){
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
*/

void Chunk::updateMesh(const World& world){
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for(int x = 0; x < CHUNK_SIZE; x++)
    for(int y = 0; y < CHUNK_HEIGHT; y++)
    for(int z = 0; z < CHUNK_SIZE; z++){
        BlockType b = blocks[x][y][z];
        if(b == AIR) continue;

        int wx = this->localPos.x + x, wy = this->localPos.y + y, wz = this->localPos.z + z;
        bool faces[6] = {
            !isSolid(world.getBlock(wx,   wy+1, wz  )), // top
            !isSolid(world.getBlock(wx,   wy-1, wz  )), // bottom
            !isSolid(world.getBlock(wx,   wy,   wz-1)), // north
            !isSolid(world.getBlock(wx,   wy,   wz+1)), // south
            !isSolid(world.getBlock(wx+1, wy,   wz  )), // east
            !isSolid(world.getBlock(wx-1, wy,   wz  ))  // west
        };
        addCube(vertices, indices, glm::ivec3(wx, wy, wz), b, faces);
    }

    bool first = !meshCreated;
    if(first){
        vao.Create();
        vbo.Create();
        ebo.Create();
        meshCreated = true;
    }

    vao.Bind();
    vbo.Update(vertices.data(), vertices.size() * sizeof(float));
    ebo.Update(indices.data(),  indices.size()  * sizeof(unsigned int)); // queda ligado al VAO
    if(first) applyVertexFormat(vao, vbo);
    vao.Unbind();   // NO desbindear el EBO antes de esto

    indexCount = (GLsizei)indices.size();
    dirty = false;
}

void Chunk::draw(){
    if(indexCount == 0) return;
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}