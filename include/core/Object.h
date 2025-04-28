// include/core/Object.h
#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "core/Component.h"

class Object
{
public:
    std::vector<std::shared_ptr<Component>> components;

    // Transformation attributes
    glm::vec3 Position;
    glm::vec3 Rotation; // Euler angles (Yaw, Pitch, Roll) in degrees
    glm::vec3 Scale;

    glm::mat4 ModelMatrix; // Cached Model Matrix

    Object();
    ~Object() = default;

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        std::shared_ptr<T> comp = std::make_shared<T>(this, std::forward<Args>(args)...);
        components.push_back(comp);
        return comp;
    }

    void SetPosition(const glm::vec3& pos);
    void SetRotation(const glm::vec3& rot);
    void SetScale(const glm::vec3& scale);
    void UpdateModelMatrix();

    void Update(float deltaTime);
    void Render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cameraPos);
};
