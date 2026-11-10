#include"../include/Block.h"

//textures id's
static constexpr int TILE_GRASS_TOP  = 0;
static constexpr int TILE_GRASS_SIDE = 3;
static constexpr int TILE_DIRT       = 2;

//orden TOP, BOTTOM, NORTH, SOUTH, EAST, WEST
static const BlockInfo blockTable[BLOCK_TYPE_COUNT] = {
    {false},
    //GRASS
    { { TILE_GRASS_TOP, TILE_DIRT,
        TILE_GRASS_SIDE, TILE_GRASS_SIDE, TILE_GRASS_SIDE, TILE_GRASS_SIDE }, true },
};

const BlockInfo& getBlockInfo(BlockType type) {
    return blockTable[type];
}

int getTile(BlockType type, Face face) {
    return blockTable[type].tiles[face];
}

bool isSolid(BlockType type) {
    return blockTable[type].solid;
}