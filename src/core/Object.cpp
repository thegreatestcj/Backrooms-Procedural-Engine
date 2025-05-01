// src/core/Object.cpp
#include "core/Object.h"
#include "core/MeshComponent.h"
#include "core/MaterialComponent.h"
#include <glm/gtc/matrix_transform.hpp>

Object::Object()
    : Position(0.0f), Rotation(0.0f), Scale(1.0f), ModelMatrix(1.0f)
{}

void Object::SetPosition(const glm::vec3& pos)
{
    Position = pos;
    UpdateModelMatrix();
}

void Object::SetRotation(const glm::vec3& rot)
{
    Rotation = rot;
    UpdateModelMatrix();
}

void Object::SetScale(const glm::vec3& scale)
{
    Scale = scale;
    UpdateModelMatrix();
}

void Object::UpdateModelMatrix()
{
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, Position);
    mat = glm::rotate(mat, glm::radians(Rotation.y), glm::vec3(0, 1, 0)); // Yaw (Y)
    mat = glm::rotate(mat, glm::radians(Rotation.x), glm::vec3(1, 0, 0)); // Pitch (X)
    mat = glm::rotate(mat, glm::radians(Rotation.z), glm::vec3(0, 0, 1)); // Roll (Z)
    mat = glm::scale(mat, Scale);
    ModelMatrix = mat;
}

void Object::Update(float deltaTime)
{
    for (auto& comp : components)
    {
        comp->Update(deltaTime);
    }
}

void Object::Render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cameraPos)
{
    MaterialComponent* materialComp = nullptr;
    MeshComponent* meshComp = nullptr;

    for (auto& comp : components)
    {
        if (!materialComp)
            materialComp = dynamic_cast<MaterialComponent*>(comp.get());
        if (!meshComp)
            meshComp = dynamic_cast<MeshComponent*>(comp.get());
    }

    if (materialComp && meshComp)
    {
        Shader* shader = materialComp->material.shader;
        if (shader)
        {
            shader->use();
            shader->setMat4("projection", projection);
            shader->setMat4("view", view);
            shader->setVec3("lightPos", glm::vec3(10.0f, 10.0f, 10.0f));
            shader->setVec3("viewPos", cameraPos);
            shader->setMat4("model", ModelMatrix);
        }

        meshComp->Render();
    }
}
