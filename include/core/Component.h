// include/core/Component.h
#pragma once

class Object; // forward declaration

class Component
{
public:
    Object* owner; // to its owner

    Component(Object* owner) : owner(owner) {}
    virtual ~Component() = default;

    virtual void Update(float deltaTime) {} // logic component
    virtual void Render() {}                // mesh component
};
