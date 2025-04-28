// include/core/Mesh.h
#pragma once

#include <vector>
#include "Basic.h" // Vector3, Vector2
#include "Vertex.h"      // Vertex struct

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO; // OpenGL buffers

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw() const;

private:
    void setupMesh();
};
