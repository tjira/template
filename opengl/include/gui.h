#pragma once

#include <ImGuiFileDialog.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "glfwpointer.h"

class Gui {
public:
    Gui(GLFWwindow* window); ~Gui();
    void render();

private:
    GLFWwindow* window;
};
