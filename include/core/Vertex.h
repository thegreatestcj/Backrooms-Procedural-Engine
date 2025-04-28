// include/core/Vertex.h
#pragma once

#include "core/Basic.h"

struct Vertex
{
    Vector3 Position;
    Vector3 Normal;
    Vector2 TexCoords;

    Vertex() = default;

    Vertex(const Vector3& position, const Vector3& normal, const Vector2& texCoords)
        : Position(position), Normal(normal), TexCoords(texCoords) {}
};
