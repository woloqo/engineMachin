#include "../include/MeshBuilder.h"

static const FaceVertex faceTemplate[FACE_COUNT][4] = {
    //top(+Y)
    {
        {{0, 1, 1}, {0, 0}},
        {{1, 1, 1}, {1, 0}},
        {{1, 1, 0}, {1, 1}},
        {{0, 1, 0}, {0, 1}},
    },
    //bottom (-Y)
    {
        {{0, 0, 0}, {0, 0}},
        {{1, 0, 0}, {1, 0}},
        {{1, 0, 1}, {1, 1}},
        {{0, 0, 1}, {0, 1}},
    },
    //north (-Z)
    {
        {{1, 0, 0}, {0, 0}},
        {{0, 0, 0}, {1, 0}},
        {{0, 1, 0}, {1, 1}},
        {{1, 1, 0}, {0, 1}},
    },
    //south (+Z)
    {
        {{0, 0, 1}, {0, 0}},
        {{1, 0, 1}, {1, 0}},
        {{1, 1, 1}, {1, 1}},
        {{0, 1, 1}, {0, 1}},
    },
    //east (+X)
    {
        {{1, 0, 1}, {0, 0}},
        {{1, 0, 0}, {1, 0}},
        {{1, 1, 0}, {1, 1}},
        {{1, 1, 1}, {0, 1}},
    },
    //west (-X)
    {
        {{0, 0, 0}, {0, 0}},
        {{0, 0, 1}, {1, 0}},
        {{0, 1, 1}, {1, 1}},
        {{0, 1, 0}, {0, 1}},
    },
};


void addFace(std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::ivec3 blockPos, Face face, BlockType type){
    int tile = getTile(type, face);
    UVRect rect = tileToUvRect(tile);
    int inicio = vertices.size() / FLOATS_PER_VERTEX;
    
    for(int i = 0; i < 4; i++){
        const FaceVertex& v = faceTemplate[face][i];
        glm::vec3 pos = glm::vec3(blockPos) + v.pos;
        glm::vec2 uv  = localToAtlasUV(v.uv, rect);

        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        vertices.push_back(uv.x);
        vertices.push_back(uv.y);
    }

    indices.push_back(inicio + 0);
    indices.push_back(inicio + 1);
    indices.push_back(inicio + 2);
    indices.push_back(inicio + 0);
    indices.push_back(inicio + 2);
    indices.push_back(inicio + 3);
}
             
void addCube(std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::ivec3 blockPos, BlockType type){
    for (int f = 0; f < FACE_COUNT; f++) addFace(vertices, indices, blockPos, static_cast<Face>(f), type);
}