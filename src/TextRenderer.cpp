#include "../include/TextRenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

TextRenderer::TextRenderer(const char* vertPath, const char* fragPath): shader(vertPath, fragPath){
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool TextRenderer::Load(const std::string& fontPath, unsigned int pixelHeight){
    FT_Library ft;
    if(FT_Init_FreeType(&ft)){
        std::cout<<"Error: no se pudo iniciar FreeType\n";
        return false;
    }

    FT_Face face;
    if(FT_New_Face(ft, fontPath.c_str(), 0, &face)){
        std::cout<<"Error: no se pudo cargar la fuente: " << fontPath << "\n";
        FT_Done_FreeType(ft);
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, pixelHeight);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(unsigned char c = 0; c < 128; c++){
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout<<"Glifo #"<<(int)c<<" no existe\n";
            continue;
        }

        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                    face->glyph->bitmap.width, face->glyph->bitmap.rows,
                    0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // o GL_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character ch = {
            tex,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left,  face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
        characters.insert({c, ch});
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return true;
}

void TextRenderer::Draw(const std::string& text, float x, float y, float scale, glm::vec3 color, int screenW, int screenH){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    shader.use();
    glm::mat4 proj = glm::ortho(0.0f, (float)screenW, 0.0f, (float)screenH);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glUniform1i(glGetUniformLocation(shader.ID, "text"), 0);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    for(char c : text){
        auto it = characters.find((unsigned char)c);
        if(it == characters.end()) continue;
        const Character& ch = it->second;

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;
        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // avanzar el cursor
        x += (ch.advance >> 6) * scale; 
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void TextRenderer::Delete(){
    for (auto& [c, ch] : characters) glDeleteTextures(1, &ch.textureID);
    characters.clear();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    shader.Delete();
}