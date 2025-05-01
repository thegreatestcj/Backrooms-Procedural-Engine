// src/core/Camera.cpp
#include "core/Camera.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position)
    : Position(position), Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
      Yaw(-90.0f), Pitch(0.0f), MovementSpeed(3.0f), MouseSensitivity(0.1f), Zoom(60.0f),
      Target(glm::vec3(0.0f)), DistanceToTarget(5.0f), Mode(CameraMode::FirstPerson)
{
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    if (Mode == CameraMode::FirstPerson)
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
    else
    {
        glm::vec3 camPos = Target - Front * DistanceToTarget;
        return glm::lookAt(camPos, Target, Up);
    }
}

void Camera::ProcessKeyboard(GLFWwindow* window, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        velocity *= 2.0f;
    }

    if (Mode == CameraMode::FirstPerson)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            Position += Front * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            Position -= Front * velocity;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            Position -= Right * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            Position += Right * velocity;
    }
    else if (Mode == CameraMode::ThirdPerson)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            Pitch += 30.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            Pitch -= 30.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            Yaw -= 30.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            Yaw += 30.0f * deltaTime;

        // Clamp pitch
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;

        updateCameraVectors();
    }

    // Ctrl zoom
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
    {
        Zoom -= 50.0f * deltaTime;
        if (Zoom < 30.0f) Zoom = 30.0f;
    }
    else
    {
        if (Zoom < 60.0f)
        {
            Zoom += 50.0f * deltaTime;
            if (Zoom > 60.0f) Zoom = 60.0f;
        }
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Clamp pitch
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::SwitchMode()
{
    if (Mode == CameraMode::FirstPerson)
        Mode = CameraMode::ThirdPerson;
    else
        Mode = CameraMode::FirstPerson;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::DrawImGui()
{
    if (ImGui::Begin("Camera Settings"))
    {
        ImGui::Text("Camera Mode: %s", Mode == CameraMode::FirstPerson ? "First Person" : "Third Person");
        ImGui::SliderFloat("Movement Speed", &MovementSpeed, 0.5f, 20.0f);
        ImGui::SliderFloat("Zoom (FOV)", &Zoom, 30.0f, 90.0f);
        ImGui::SliderFloat("Yaw", &Yaw, -180.0f, 180.0f);
        ImGui::SliderFloat("Pitch", &Pitch, -89.0f, 89.0f);
        if (Mode == CameraMode::ThirdPerson)
        {
            ImGui::SliderFloat("Distance to Target", &DistanceToTarget, 2.0f, 10.0f);
        }
        if (ImGui::Button("Switch Mode"))
        {
            SwitchMode();
        }
    }
    ImGui::End();
}
