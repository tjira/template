#pragma once

// graphics card and window
#include <GLFW/glfw3.h>
#include <glad/gl.h>

// mathematics for OpenGL
#include <glm/gtc/matrix_transform.hpp>

// include all C++ headers
#include <bits/stdc++.h>

// GLFW storage pointer
struct Pointer {
    const char* title = "OpenGL Template"; glm::vec2 mouse; GLFWwindow* window;
    int width = 1280, height = 720, samples = 16, major = 4, minor = 2;
    struct Camera {
        glm::mat4 view, proj;
    } camera{};
    struct Flags {
        bool info = false, objects = false, options = false;
    } flags{};
    struct Light {
        glm::vec3 ambient = {0.4f, 0.4f, 0.4f}, diffuse = {0.2f, 0.2f, 0.2f}, specular = {0.4f, 0.4f, 0.4f};
        glm::vec3 position = {4.0f, 5.0f, -2.0f};
    } light{};
};

struct Vertex {
    glm::vec3 position, normal = glm::vec3(0), color = glm::vec3(1);
};
