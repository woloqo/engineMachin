#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include "ShaderClass.h"

struct Character {
    GLuint     textureID;  // textura del glifo
    glm::ivec2 size;       // ancho y alto del bitmap
    glm::ivec2 bearing;    // offset desde la baseline (left, top)
    unsigned int advance;  // avance horizontal en 1/64 de píxel
};

class TextRenderer {
public:
    TextRenderer(const char* vertPath, const char* fragPath);

    bool Load(const std::string& fontPath, unsigned int pixelHeight);
    void Draw(const std::string& text, float x, float y, float scale,
              glm::vec3 color, int screenW, int screenH);
    void Delete();

private:
    Shader shader;
    GLuint vao = 0, vbo = 0;
    std::map<unsigned char, Character> characters;
};

#endif