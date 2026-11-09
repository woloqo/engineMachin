#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<math.h>
#include<vector>
#include"Block.h"
#include"Atlas.h"

const int FLOATS_PER_VERTEX = 5;

struct FaceVertex{
    glm::vec3 pos;
    glm::vec2 uv;
};

void addFace(std::vector<float>& vertices,
             std::vector<unsigned int>& indices,
             glm::ivec3 blockPos, Face face, BlockType type);

void addCube(std::vector<float>& vertices,
             std::vector<unsigned int>& indices,
             glm::ivec3 blockPos, BlockType type);

#endif