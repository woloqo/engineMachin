#ifndef TEXTURES_H
#define TEXTURES_H

#include"stb_image.h"
#include<bits/stdc++.h>

class Texture{
public:
    int width;
    int height;
    int numColCh;
    unsigned int ID;
    std::string name;

    unsigned char* bytes;

    Texture(std::string name, const char* texutrePath);

    void Delete();
    void bind();

};

#endif