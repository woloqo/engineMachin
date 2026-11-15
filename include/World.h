#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <memory>
#include <climits>
#include <glm/glm.hpp>
#include "Chunk.h"
#include "Block.h"
#include "FastNoise.h"

const int WORLD_SIZE = 3;

struct IVec2Hash{
    size_t operator()(const glm::ivec2& v) const {
        return (size_t)(v.x * 73856093) ^ (size_t)(v.y * 19349663);
    }
};

class World{
public:
    BlockType getBlock(int wx, int wy, int wz) const;
    void setBlock(int wx, int wy, int wz, BlockType t);

    void update(int maxPerFrame = INT_MAX);   // remalla chunks sucios
    void render();

    World(int n);

    void generateWorld();

private:
    std::unordered_map<glm::ivec2, std::unique_ptr<Chunk>, IVec2Hash> chunks;

    Chunk* getChunk(glm::ivec2 c) const;
    void markDirty(glm::ivec2 c);
};

#endif