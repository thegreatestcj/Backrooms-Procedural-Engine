// include/core/Material.h
#pragma once

#include <string>
#include "core/Shader.h"
#include "core/Texture.h"

class Material
{
public:
    Shader* shader;     // Shader pointer
    Texture* texture;   // Texture pointer (optional)

    Material();
    Material(Shader* shader, Texture* texture = nullptr);
    ~Material();

    void Use() const;
};
