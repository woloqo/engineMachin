#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Chunk.h"

const int WORLD_SIZE = 3;

class World{
public:
    Chunk chunks [WORLD_SIZE][WORLD_SIZE];

    World(int n, std::vector<float>& vertices, std::vector<unsigned int>& indices);
};

#endif