// include/core/Camera.h
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

enum class CameraMode
{
    FirstPerson,
    ThirdPerson
};

class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;

    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // TPS specific
    glm::vec3 Target; // Third person focus target
    float DistanceToTarget;

    CameraMode Mode;

    Camera(glm::vec3 position);

    glm::mat4 GetViewMatrix() const;

    void ProcessKeyboard(GLFWwindow* window, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset);
    void SwitchMode();
    void DrawImGui();

private:
    void updateCameraVectors();
};
