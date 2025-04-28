//
// Created by saki on 4/27/25.
//
// src/main.cpp

#include <../external/glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "core/Shader.h"
#include "core/Object.h"
#include "core/MeshComponent.h"
#include "core/MaterialComponent.h"
#include "core/Camera.h"
#include "utilities/CreatePlaneMesh.h"

#include <iostream>
#include <vector>
#include <memory>

// Cross-platform header for changing working directory
#ifdef _WIN32
#include <direct.h> // For Windows _chdir()
#else
#include <unistd.h> // For Linux, WSL, and macOS chdir()
#endif

// Change current working directory to project root
void SetWorkingDirectoryToProjectRoot()
{
#ifdef _WIN32
    _chdir("../../");
#else
    chdir("../../");
#endif
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    SetWorkingDirectoryToProjectRoot();
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Procedural Backrooms", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Load Shader
    Shader wallpaperShader("DefaultWallpaper.vert", "DefaultWallpaper.frag");

    // Create Plane Mesh
    Mesh planeMesh = CreatePlaneMesh(50.0f, 50.0f, 4.0f);

    // Create Objects
    std::vector<std::shared_ptr<Object>> sceneObjects;

    // Floor
    auto floor = std::make_shared<Object>();
    floor->AddComponent<MeshComponent>(planeMesh);
    floor->AddComponent<MaterialComponent>(Material(&wallpaperShader));
    sceneObjects.push_back(floor);

    // Ceiling
    auto ceiling = std::make_shared<Object>();
    ceiling->AddComponent<MeshComponent>(planeMesh);
    ceiling->AddComponent<MaterialComponent>(Material(&wallpaperShader));
    sceneObjects.push_back(ceiling);

    // Walls (Front, Back, Left, Right)
    for (int i = 0; i < 4; ++i)
    {
        auto wall = std::make_shared<Object>();
        wall->AddComponent<MeshComponent>(planeMesh);
        wall->AddComponent<MaterialComponent>(Material(&wallpaperShader));
        sceneObjects.push_back(wall);
    }

    // Camera
    Camera camera(glm::vec3(0.0f, 2.0f, 5.0f));

    // Timing
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        camera.ProcessKeyboard(window, deltaTime);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Camera ImGui
        camera.DrawImGui();

        // Clear Screen
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup camera matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)display_w / (float)display_h, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        wallpaperShader.use();
        wallpaperShader.setMat4("projection", projection);
        wallpaperShader.setMat4("view", view);
        wallpaperShader.setVec3("lightPos", glm::vec3(10.0f, 10.0f, 10.0f));
        wallpaperShader.setVec3("viewPos", camera.Position);

        // Transformations
        glm::mat4 model(1.0f);

        // Floor
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
        floor->components[0]->Render();

        // Ceiling
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 5.0f, 0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
        ceiling->components[0]->Render();

        // Walls
        glm::vec3 wallPositions[] = {
            glm::vec3(0, 2.5f, -25),
            glm::vec3(0, 2.5f, 25),
            glm::vec3(-25, 2.5f, 0),
            glm::vec3(25, 2.5f, 0)
        };
        glm::vec3 wallRotations[] = {
            glm::vec3(0, 0, 0),
            glm::vec3(0, 180, 0),
            glm::vec3(0, 90, 0),
            glm::vec3(0, -90, 0)
        };

        for (int i = 2; i < 6; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, wallPositions[i-2]);
            model = glm::rotate(model, glm::radians(wallRotations[i-2].y), glm::vec3(0, 1, 0));
            sceneObjects[i]->components[0]->Render();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}