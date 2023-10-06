#pragma once

#include "mesh.h"
#include <GLFW/glfw3.h>

#define WIDTH 1024
#define HEIGHT 576

struct GLFWwindow;

struct GLFWPointer {
    std::string title = "OpenGL Template"; glm::vec2 mouse; GLFWwindow* window;
    int width = WIDTH, height = HEIGHT, samples = 16, major = 4, minor = 2;
    struct Camera {
        glm::mat4 view, proj;
    } camera{};
    struct Flags {
        bool info = false, options = false;
    } flags{};
    struct Light {
        float ambient = 0.4f, diffuse = 0.2f, specular = 0.4f, shininess = 4.0f;
        glm::vec3 position = {1.0f, 1.0f, 1.0f};
    } light{};
};
