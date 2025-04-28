# 后室逃脱风格 程序化生成引擎

[English](README.md) | [🇨🇳 中文版](README.zh-CN.md)

## 项目简介
欢迎来到后室！  
本项目使用 **C++ & OpenGL** 编写，旨在实时程序化生成无限延伸的后室风格三维环境。

✨ **主要功能：**
- 完全程序化生成房间、走廊及连接关系
- 支持动态调整地图规模（可自由调整生成区域大小）
- 支持重新随机化打乱（使用不同随机种子生成）
- 材质系统（支持简单的 PBR 材质，包含纹理与表面参数）
- 支持模型/场景导入与导出
- 支持通过图形界面实时调整参数（如房间尺寸、材质设置、光照强度等）—— 致谢ImGui👏
- 支持后处理效果（如泛光 Bloom、色调映射等）

项目目标是构建一个轻量但可扩展的 MVP（最小可行产品），为后续发展为完整引擎打下坚实基础。

## 🛠️ 跨平台依赖说明

本项目已经包含了大部分**头文件型或可移植的依赖库**，包括：
- [GLAD](https://glad.dav1d.de/) - OpenGL 函数加载器
- [GLM](https://github.com/g-truc/glm) - OpenGL 数学运算库
- [Dear ImGui](https://github.com/ocornut/imgui) - 即时模式 GUI 库

**这些依赖无需单独下载，已随仓库提供。**

但仍需手动安装一些**系统级依赖**：
- **OpenGL** 运行环境（大多数系统已预装）
- **GLFW**（用于窗口管理与输入处理）
- **CMake**（用于构建项目）

🔧 **各平台安装指南：**

**Windows：**
- 安装 [CMake](https://cmake.org/download/) 及（可选）[vcpkg](https://github.com/microsoft/vcpkg)
- 通过 vcpkg 安装 GLFW（命令：`vcpkg install glfw3`）
- 确保显卡驱动支持 OpenGL 3.3 Core Profile 及以上版本

**Linux（以 Ubuntu 为例）：**
```bash
sudo apt update
sudo apt install libglfw3-dev libgl1-mesa-dev cmake

**macOS:**
```bash
brew install glfw cmake
```
