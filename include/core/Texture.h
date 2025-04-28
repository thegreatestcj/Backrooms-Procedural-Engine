// include/core/Texture.h
#pragma once

#include <string>

class Texture
{
public:
    unsigned int ID;        // OpenGL texture ID
    std::string type;       // "diffuse", "specular", "procedural" etc.
    std::string path;       // For file loaded textures (optional)

    Texture();
    ~Texture();

    // Load texture from file
    bool LoadFromFile(const std::string& filepath);

    // Generate texture from raw data (procedural textures)
    bool GenerateFromData(unsigned char* data, int width, int height, bool alpha = false);

    // Bind texture to a texture unit
    void Bind(unsigned int unit = 0) const;
};
