// include/core/MeshComponent.h
#pragma once

#include "core/Component.h"
#include "core/Mesh.h"

class MeshComponent : public Component
{
public:
    Mesh mesh;

    MeshComponent(Object* owner, const Mesh& meshData)
        : Component(owner), mesh(meshData) {}

    void Render() override;
};
