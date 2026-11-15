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

#include"VAO.h"
#include"VBO.h"

/*
--- Learn OpenGL - Graphics programming Learn modern OpenGL (pag 34) ---

The first parameter specifies which vertex attribute we want to configure. Remember that we
specified the location of the position vertex attribute in the vertex shader with layout
(location = 0). This sets the location of the vertex attribute to 0 and since we want to
pass data to this vertex attribute, we pass in 0.

• The next argument specifies the size of the vertex attribute. The vertex attribute is a vec3 so
it is composed of 3 values.

• The third argument specifies the type of the data which is GL_FLOAT (a vec* in GLSL
consists of floating point values).

• The next argument specifies if we want the data to be normalized. If we’re inputting integer
data types (int, byte) and we’ve set this to GL_TRUE, the integer data is normalized to 0 (or
-1 for signed data) and 1 when converted to float. This is not relevant for us so we’ll leave
this at GL_FALSE.

• The fifth argument is known as the stride and tells us the space between consecutive vertex
attributes. Since the next set of position data is located exactly 3 times the size of a float
away we specify that value as the stride. Note that since we know that the array is tightly
packed (there is no space between the next vertex attribute value) we could’ve also specified
the stride as 0 to let OpenGL determine the stride (this only works when values are tightly
packed). Whenever we have more vertex attributes we have to carefully define the spacing
between each vertex attribute but we’ll get to see more examples of that later on.

• The last parameter is of type void* and thus requires that weird cast. This is the offset of
where the position data begins in the buffer. Since the position data is at the start of the data
array this value is just 0. We will explore this parameter in more detail later on

void PFNGLVERTEXATTRIBPOINTERPROC(
    GLuint index, 
    GLint size, 
    GLenum type, 
    GLboolean normalized, 
    GLsizei stride, 
    const void *pointer)

*/

struct FaceVertex{
    glm::vec3 pos;
    glm::vec2 uv;
};

struct VertexAttrib{
    GLuint  layout;
    GLint   components;
    GLenum  type;
    size_t  offset;   // en bytes
};

// Formato de vértice: pos(3) + uv(2)
inline constexpr VertexAttrib VERTEX_FORMAT[] = {
    { 0, 3, GL_FLOAT, 0 },
    { 1, 2, GL_FLOAT, 3 * sizeof(float) },
};
inline constexpr int   FLOATS_PER_VERTEX = 5;
inline constexpr GLsizei VERTEX_STRIDE   = FLOATS_PER_VERTEX * sizeof(float);

void applyVertexFormat(VAO& vao, VBO& vbo);

void addFace(std::vector<float>& vertices,
             std::vector<unsigned int>& indices,
             glm::ivec3 blockPos, Face face, BlockType type);

void addCube(std::vector<float>& vertices,
             std::vector<unsigned int>& indices,
             glm::ivec3 blockPos, BlockType type, bool facesToDraw[6]);

#endif