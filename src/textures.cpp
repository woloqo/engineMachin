#include"../include/textures.h"
#include"../include/stb_image.h"
#include<glad/glad.h>
#include<bits/stdc++.h>

Texture::Texture(std::string name, const char* texturePath){

    this->name = name;

    stbi_set_flip_vertically_on_load(true);
    bytes = stbi_load(texturePath, &width, &height, &numColCh, 0);

    GLenum format = GL_RGB;
    if(numColCh == 4)      format = GL_RGBA;
    else if(numColCh == 1) format = GL_RGB;

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  ID);
    std::cout<<"Textura ("<<this->name<<") creada correctamente\n";

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, ID);
}