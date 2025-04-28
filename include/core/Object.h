// include/core/Object.h
#pragma once

#include <vector>
#include <memory>
#include "core/Component.h"

class Object
{
public:
    std::vector<std::shared_ptr<Component>> components;

    Object() = default;
    ~Object() = default;

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        std::shared_ptr<T> comp = std::make_shared<T>(this, std::forward<Args>(args)...);
        components.push_back(comp);
        return comp;
    }

    void Update(float deltaTime);
    void Render();
};
