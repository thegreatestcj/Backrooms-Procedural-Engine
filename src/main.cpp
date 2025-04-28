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

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

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

    // Load shaders
    Shader wallpaperShader("DefaultWallpaper.vert", "DefaultWallpaper.frag");
    Shader floorShader("DefaultFloor.vert", "DefaultFloor.frag");
    Shader ceilingShader("DefaultCeiling.vert", "DefaultCeiling.frag");

    // Create plane mesh
    Mesh planeMesh = CreatePlaneMesh(50.0f, 50.0f, 4.0f);

    // Create scene objects
    std::vector<std::shared_ptr<Object>> sceneObjects;

    auto floor = std::make_shared<Object>();
    floor->AddComponent<MeshComponent>(planeMesh);
    floor->AddComponent<MaterialComponent>(Material(&floorShader));
    floor->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f)); // Rotate onto XZ plane
    sceneObjects.push_back(floor);

    auto ceiling = std::make_shared<Object>();
    ceiling->AddComponent<MeshComponent>(planeMesh);
    ceiling->AddComponent<MaterialComponent>(Material(&ceilingShader));
    ceiling->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
    ceiling->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
    sceneObjects.push_back(ceiling);

    glm::vec3 wallPositions[4] = {
        glm::vec3(0, 2.5f, -25),
        glm::vec3(0, 2.5f, 25),
        glm::vec3(-25, 2.5f, 0),
        glm::vec3(25, 2.5f, 0)
    };
    float wallRotationsY[4] = { 0.0f, 180.0f, 90.0f, -90.0f };

    for (int i = 0; i < 4; ++i)
    {
        auto wall = std::make_shared<Object>();
        wall->AddComponent<MeshComponent>(planeMesh);
        wall->AddComponent<MaterialComponent>(Material(&wallpaperShader));
        wall->SetPosition(wallPositions[i]);
        wall->SetRotation(glm::vec3(0, wallRotationsY[i], 0));
        sceneObjects.push_back(wall);
    }

    // Create camera
    Camera camera(glm::vec3(0.0f, 2.0f, 5.0f));
    float lastFrame = 0.0f;

    // Main loop
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

        camera.DrawImGui();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)display_w / (float)display_h, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        for (auto& obj : sceneObjects)
        {
            obj->Render(projection, view, camera.Position);
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
