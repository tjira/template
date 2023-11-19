#pragma once

#include "scene.h"

// OpenGL and GLFW backends
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

// OpenGL file dialog
#include <ImGuiFileDialog.h>

class Gui {
public:
    // constructors and destructors
    Gui(GLFWwindow* window); ~Gui();

    // state functions
    void render(Scene& scene);

private:
    GLFWwindow* window;
};
