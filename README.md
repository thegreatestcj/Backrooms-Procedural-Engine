# Escape-the-Backrooms Style Procedural Engine

[English](README.md) | [🇨🇳 中文版](README.zh-CN.md)

## Introduction
Welcome to the Backrooms!  
This project is a real-time procedural 3D engine written in **C++ & OpenGL**, designed for procedural generation of endless Backrooms-style environments.

✨ **Main Features:**
- Fully procedural generation of rooms, corridors, and their connections
- Dynamic size adjustment (resize the generated map)
- Random re-generation (shuffle the map with different seeds)
- Material system with simple PBR support (textures and surface parameters)
- Model/Scene import and export support
- Parametric control through GUI (room size, texture settings, light intensity, etc.) Kudos to ImGui👏
- Post-processing effects (e.g., bloom, tone mapping, etc.)

The goal is to create a minimal, extendable MVP, while providing a solid foundation for future expansion into a full engine.

## 🛠️ Cross-platform Dependencies

This project includes most header-only or portable dependencies **already in the repository**, such as:
- [GLAD](https://glad.dav1d.de/) - OpenGL function loader
- [GLM](https://github.com/g-truc/glm) - OpenGL Mathematics Library
- [Dear ImGui](https://github.com/ocornut/imgui) - Immediate Mode GUI Library

You **don't need to download them separately**.

However, you still **need to install some system libraries manually**:
- **OpenGL** runtime (usually pre-installed)
- **GLFW** for window and input handling
- **CMake** for building the project

🔧 **Installation (per platform):**

**Windows:**
- Install [CMake](https://cmake.org/download/) and [vcpkg](https://github.com/microsoft/vcpkg) (optional)
- Install GLFW (can use vcpkg: `vcpkg install glfw3`)
- Make sure your GPU driver supports OpenGL 3.3 Core or above

**Linux (Ubuntu example):**
```bash
sudo apt update
sudo apt install libglfw3-dev libgl1-mesa-dev cmake
```
**macOS:**
```bash
brew install glfw cmake
```
