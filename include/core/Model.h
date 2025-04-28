// include/core/Model.h
#pragma once

#include <vector>
#include "core/Mesh.h"

class Model
{
public:
    std::vector<Mesh> meshes;

    Model() = default;
    ~Model() = default;

    void AddMesh(const Mesh& mesh);
    void Draw() const;
};
