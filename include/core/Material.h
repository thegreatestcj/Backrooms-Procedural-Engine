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
    Material(Shader* shader, const glm::vec3& baseColor, Texture* texture = nullptr);
    ~Material();

    glm::vec3 baseColor = glm::vec3(1.0f); // Base Color
    float metallic = 0.0f;                 // Metalness (for PBR)
    float roughness = 1.0f;                // Roughness (for PBR)
    float ambient = 0.1f;                  // Ambient Intensity
    float diffuse = 0.8f;                  // Diffuse Intensity
    float specular = 0.5f;                 // Specular Intensity

    void Use() const;
};
