cmake_minimum_required(VERSION 3.14)

project(BackroomsProceduralEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect platform
if(WIN32)
    message(STATUS "Detected platform: Windows")
elseif(APPLE)
    message(STATUS "Detected platform: macOS")
elseif(UNIX)
    message(STATUS "Detected platform: Linux/Unix")
endif()

# Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external
        ${CMAKE_SOURCE_DIR}/external/glad
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui/backends
)

# Source files
file(GLOB_RECURSE SRC_FILES
        src/*.cpp
)

# ImGui core source files
file(GLOB IMGUI_CORE_FILES
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_demo.cpp
)

# ImGui backend source files
set(IMGUI_BACKEND_FILES
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)

# GLAD source file
file(GLOB GLAD_FILES
        external/glad/*.c
)

# Combine all sources
set(ALL_SOURCES
        ${SRC_FILES}
        ${IMGUI_CORE_FILES}
        ${IMGUI_BACKEND_FILES}
        ${GLAD_FILES}
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# Set different output directories for Debug and Release
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        glfw
)

# Automatically define _DEBUG when building Debug
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
)