#ifndef ATLAS_H
#define ATLAS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<math.h>

const int ATLAS_SIZE 	= 256;
const int TILES_SIZE 	= 16;
const int TILES_PER_ROW = 16;
const float TILE_UV_SIZE= 1.0 / TILES_PER_ROW;  

struct UVRect {
    glm::vec2 min;
    glm::vec2 max;

    UVRect(float uMin, float vMin, float uMax, float vMax)
        : min(uMin, vMin), max(uMax, vMax) {}
};

glm::vec2 localToAtlasUV(glm::vec2 localUV, const UVRect& rect);
UVRect tileToUvRect(int tileId);

#endif