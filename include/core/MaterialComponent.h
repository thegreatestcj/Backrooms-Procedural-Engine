// include/core/MaterialComponent.h
#pragma once

#include "core/Component.h"
#include "core/Material.h"

class MaterialComponent : public Component
{
public:
    Material material;

    MaterialComponent(Object* owner, const Material& mat)
        : Component(owner), material(mat) {}

    void Render() override
    {
        material.Use();
    }

    void DrawImGui() override;
};
