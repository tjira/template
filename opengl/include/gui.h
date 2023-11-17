#pragma once

#include "opengl.h"

// OpenGL and GLFW backends
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

// OpenGL file dialog
#include <ImGuiFileDialog.h>

class Gui {
public:
    Gui(GLFWwindow* window); ~Gui();
    void render();

private:
    GLFWwindow* window;
};
