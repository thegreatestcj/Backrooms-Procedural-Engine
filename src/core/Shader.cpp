// src/core/Shader.cpp
#include "core/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

// Default shader folders
const std::string vertexShaderPath = "shaders/vertex/";
const std::string fragmentShaderPath = "shaders/fragment/";

Shader::Shader(const char* vertexFileName, const char* fragmentFileName)
{
    // Build full file paths
    std::string vertexFullPath = vertexShaderPath + vertexFileName;
    std::string fragmentFullPath = fragmentShaderPath + fragmentFileName;

    // Load Vertex Shader source code
    std::string vertexCode;
    std::ifstream vShaderFile(vertexFullPath);
    if (!vShaderFile)
    {
        std::cerr << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ: " << vertexFullPath << "\n";
    }
    else
    {
        std::stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vertexCode = vShaderStream.str();
    }

    // Load Fragment Shader source code
    std::string fragmentCode;
    std::ifstream fShaderFile(fragmentFullPath);
    if (!fShaderFile)
    {
        std::cerr << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ: " << fragmentFullPath << "\n";
    }
    else
    {
        std::stringstream fShaderStream;
        fShaderStream << fShaderFile.rdbuf();
        fragmentCode = fShaderStream.str();
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile Vertex Shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    // Compile Fragment Shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    // Link shaders into a program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // Delete the intermediate shaders; they are now linked into the program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::use() const
{
    glUseProgram(ID);
}

// Other uniform set methods (setBool, setInt, setFloat, etc.) remain unchanged
