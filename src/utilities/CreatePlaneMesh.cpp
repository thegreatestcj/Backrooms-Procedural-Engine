// src/utilities/CreatePlaneMesh.cpp
#include "utilities/CreatePlaneMesh.h"

Mesh CreatePlaneMesh(float width, float height, float uvRepeat)
{
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;

    std::vector<Vertex> vertices = {
        Vertex({-halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}),
        Vertex({ halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {uvRepeat, 0.0f}),
        Vertex({ halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {uvRepeat, uvRepeat}),
        Vertex({-halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, uvRepeat})
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    return Mesh(vertices, indices);
}
