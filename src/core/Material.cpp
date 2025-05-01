// src/core/Material.cpp
#include "core/Material.h"

Material::Material()
    : shader(nullptr), texture(nullptr)
{
}

Material::Material(Shader* shader, const glm::vec3& baseColor, Texture* texture)
    : shader(shader), texture(texture), baseColor(baseColor)
{
}

Material::~Material()
{
    // Don't delete shader or texture! They are managed outside.
}

void Material::Use() const
{
    if (shader)
    {
        shader->use();
        if (texture)
        {
            shader->setInt("texture1", 0); // set sampler uniform
            texture->Bind(0);              // bind to texture unit 0
        }
    }

    shader->setVec3("material.baseColor", baseColor);
    shader->setFloat("material.metallic", metallic);
    shader->setFloat("material.roughness", roughness);
    shader->setFloat("material.ambient", ambient);
    shader->setFloat("material.diffuse", diffuse);
    shader->setFloat("material.specular", specular);
}


