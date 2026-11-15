#include "../include/World.h"


static int floorDiv(int a, int b){   // b > 0
    int q = a / b;
    if((a % b != 0) && (a < 0)) --q;
    return q;
}

World::World(int n){
    for(int x = 0; x < n; x++)
        for(int z = 0; z < n; z++){
            glm::ivec2 c(x, z);
            chunks[c] = std::make_unique<Chunk>(c);
        }
    update();
}

void World::generateWorld(){
    FastNoise noise(1337); //default seed
}

Chunk* World::getChunk(glm::ivec2 c) const {
    auto it = chunks.find(c);
    return it == chunks.end() ? nullptr : it->second.get();
}

void World::markDirty(glm::ivec2 c){
    if(Chunk* ch = getChunk(c)) ch->dirty = true;
}

BlockType World::getBlock(int wx, int wy, int wz) const {
    if(wy < 0) return STONE;              // suelo sólido: no dibujar cara inferior
    if(wy >= CHUNK_HEIGHT) return AIR;

    glm::ivec2 c(floorDiv(wx, CHUNK_SIZE), floorDiv(wz, CHUNK_SIZE));
    Chunk* ch = getChunk(c);
    if(!ch) return STONE;                 // fuera del mundo: sólido (sin caras al vacío)

    return ch->getBlock(wx - c.x * CHUNK_SIZE, wy, wz - c.y * CHUNK_SIZE);
}

void World::setBlock(int wx, int wy, int wz, BlockType t){
    if(wy < 0 || wy >= CHUNK_HEIGHT) return;

    glm::ivec2 c(floorDiv(wx, CHUNK_SIZE), floorDiv(wz, CHUNK_SIZE));
    Chunk* ch = getChunk(c);
    if(!ch) return;

    int lx = wx - c.x * CHUNK_SIZE;
    int lz = wz - c.y * CHUNK_SIZE;
    ch->setBlock(lx, wy, lz, t);
    ch->dirty = true;

    if(lx == 0)              markDirty({c.x - 1, c.y});
    if(lx == CHUNK_SIZE - 1) markDirty({c.x + 1, c.y});
    if(lz == 0)              markDirty({c.x, c.y - 1});
    if(lz == CHUNK_SIZE - 1) markDirty({c.x, c.y + 1});
}

void World::update(int maxPerFrame){
    int done = 0;
    for(auto& [coord, ch] : chunks){
        if(!ch->dirty) continue;
        ch->updateMesh(*this);
        if(++done >= maxPerFrame) break;
    }
}

void World::render(){
    for(auto& [coord, ch] : chunks) ch->draw();
}