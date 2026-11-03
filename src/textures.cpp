#include"../include/textures.h"
#include"../include/stb_image.h"
#include<glad/glad.h>
#include<bits/stdc++.h>

Texture::Texture(std::string name, const char* texturePath){

    this->name = name;

    stbi_set_flip_vertically_on_load(true);
    bytes = stbi_load(texturePath, &width, &height, &numColCh, 0);
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  ID);
    std::cout<<"Textura ("<<this->name<<") creada correctamente\n";

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, ID);
}