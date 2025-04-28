// src/core/Object.cpp
#include "core/Object.h"

void Object::Update(float deltaTime)
{
    for (auto& comp : components)
    {
        comp->Update(deltaTime);
    }
}

void Object::Render()
{
    for (auto& comp : components)
    {
        comp->Render();
    }
}
