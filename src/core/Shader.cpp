// src/core/Shader.cpp
#include <QDebug>
#include "core/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

// Default shader folders
const std::string vertexShaderPath = "shaders/vertex/";
const std::string fragmentShaderPath = "shaders/fragment/";

Shader::Shader(const char* vertexFileName, const char* fragmentFileName)
{
    if (!glIsEnabled(GL_DEPTH_TEST)) {
        std::cerr << "⚠️ Warning: GL context may not be fully ready (GL_DEPTH_TEST not enabled yet)" << std::endl;
    }

    // Build full file paths
    std::string vertexFullPath = vertexShaderPath + vertexFileName;
    std::string fragmentFullPath = fragmentShaderPath + fragmentFileName;

    qDebug() << "[Shader] Loading:" << vertexFullPath.c_str() << "and" << fragmentFullPath.c_str();

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

    if (vertexCode.empty()) {
        std::cerr << "❌ ERROR: vertex shader source is empty: " << vertexFullPath << std::endl;
        ID = 0;
        return;
    }
    if (fragmentCode.empty()) {
        std::cerr << "❌ ERROR: fragment shader source is empty: " << fragmentFullPath << std::endl;
        ID = 0;
        return;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile Vertex Shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    // After glCompileShader(vertex);
    int success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile Fragment Shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    // Similarly after glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders into a program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

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

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

// Other uniform set methods (setBool, setInt, setFloat, etc.) remain unchanged
