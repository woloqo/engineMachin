#include "../include/World.h"

World::World(int n, std::vector<float>& vertices, std::vector<unsigned int>& indices){
    for(int x=0; x<n; x++)
        for(int z=0; z<n; z++){
            chunks[x][z] = Chunk(x+z, glm::ivec3(x*CHUNK_SIZE, 0, z*CHUNK_SIZE));
            chunks[x][z].updateMesh(vertices, indices);
        }

}