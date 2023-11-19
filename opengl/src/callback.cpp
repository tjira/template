#include "callback.h"

void keyCallback(GLFWwindow* window, int key, int, int action, int mods) {
    // if a button is pressed
    if (Pointer* pointer = (Pointer*)glfwGetWindowUserPointer(window); action == GLFW_PRESS) {

        // save the image with CTRL+S combination
        if (mods == GLFW_MOD_CONTROL && key == GLFW_KEY_S) {
            ImGuiFileDialog::Instance()->OpenDialog("Save Screenshot", "Save Screenshot", "Image Files{.png,.jpg,.bmp},All Files{.*}", "");
        }

        // function keys
        if (key == GLFW_KEY_F1) pointer->flags.options = !pointer->flags.options;
        if (key == GLFW_KEY_F2) pointer->flags.objects = !pointer->flags.objects;
        if (key == GLFW_KEY_F12) pointer->flags.info = !pointer->flags.info;
    }
}

void positionCallback(GLFWwindow* window, double x, double y) {
    // extract the GLFW pointer
    Pointer* pointer = (Pointer*)glfwGetWindowUserPointer(window);

    // if the left button is pressed and the GUI is closed
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {

        // get X and Y rotation axes
        glm::vec3 xaxis = glm::inverse(glm::mat3(pointer->camera.view)) * glm::vec3(0, 1, 0);
        glm::vec3 yaxis = glm::inverse(glm::mat3(pointer->camera.view)) * glm::vec3(1, 0, 0);

        // rotate the camera
        pointer->camera.view = glm::rotate(pointer->camera.view, 0.01f * ((float)y - pointer->mouse.y), yaxis);
        pointer->camera.view = glm::rotate(pointer->camera.view, 0.01f * ((float)x - pointer->mouse.x), xaxis);
    }

    // update mouse coordinates
    pointer->mouse = {x, y};
}

void resizeCallback(GLFWwindow* window, int width, int height) {
    // if width and height is greater than 0
    if (Pointer* pointer = (Pointer*)glfwGetWindowUserPointer(window); width > 0 && height > 0) {

        // update projection matrix and set values to GLFW struct
        pointer->camera.proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.01f, 1000.0f);
        pointer->width = width, pointer->height = height; glViewport(0, 0, width, height);
    }
}

void scrollCallback(GLFWwindow* window, double, double dy) {
    // if GUI is closed
    if (!ImGui::GetIO().WantCaptureMouse) {

        // zoom in
        ((Pointer*)glfwGetWindowUserPointer(window))->camera.view *= glm::mat4(glm::mat3(1.0f + 0.08f * (float)dy));
    }
}
