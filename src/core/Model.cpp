// src/core/Model.cpp
#include "core/Model.h"

void Model::AddMesh(const Mesh& mesh)
{
    meshes.push_back(mesh);
}

void Model::Draw() const
{
    for (const auto& mesh : meshes)
    {
        mesh.Draw();
    }
}
