#include "gui.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Gui::Gui(GLFWwindow* window) : window(window) {
    // create the context
    ImGui::CreateContext();

    // initialize OpenGL and GLFW
    ImGui_ImplOpenGL3_Init("#version 420"), ImGui_ImplGlfw_InitForOpenGL(this->window, true);

    // disable GUI state file generation
    ImGui::GetIO().IniFilename = nullptr;
}

Gui::~Gui() {
    // destruct GLFW and OpenGL
    ImGui_ImplGlfw_Shutdown(), ImGui_ImplOpenGL3_Shutdown();

    // destruct GUI context
    ImGui::DestroyContext();
}

void Gui::render() {
    // get the GLFW pointer
    Pointer* pointer = (Pointer*)glfwGetWindowUserPointer(window);

    // begin frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // options window
    if (pointer->flags.options) {

        // begin the window
        ImGui::Begin("Options", &pointer->flags.options, ImGuiWindowFlags_AlwaysAutoResize);
        
        // lighting options
        ImGui::SliderFloat("Ambient", &pointer->light.ambient, 0, 1);
        ImGui::SliderFloat("Diffuse", &pointer->light.diffuse, 0, 1);
        ImGui::SliderFloat("Specular", &pointer->light.specular, 0, 1);
        ImGui::SliderFloat("Shininess", &pointer->light.shininess, 1, 128);

        // end the window
        ImGui::End();
    }

    // info window
    if (pointer->flags.info) {

        // begin the window
        ImGui::SetNextWindowPos({ 0, 0 }); ImGui::Begin("info", &pointer->flags.info,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoFocusOnAppearing
        );

        // display the info
        ImGui::Text("%.1f", ImGui::GetIO().Framerate);

        // end the window
        ImGui::End();
    }

    // if saving the molecule open the window
    if (ImGuiFileDialog::Instance()->Display("Save Screenshot", ImGuiWindowFlags_NoCollapse, {512, 288})) {

        // get the with and height of the viewport and create pixel array
        GLint viewport[4]; glGetIntegerv(GL_VIEWPORT, viewport);
        int width = viewport[2], height = viewport[3];
        unsigned char pixels[4 * width * height];

        // read the buffer
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        // if the image save is confirmed
        if (ImGuiFileDialog::Instance()->IsOk()) {

            // get the path and extension
            std::string path = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string extension = path.substr(path.find_last_of(".") + 1);

            // flip the image
            for (int i = 0; i < 4 * width; i++) {
                for (int j = 0; j < height / 2; j++) {
                    std::swap(pixels[4 * j * width + i], pixels[4 * (height - j - 1) * width + i]);
                }
            }

            // save the buffer
            if (extension == "png") stbi_write_png(path.c_str(), width, height, 4, pixels, 4 * width);
            else if (extension == "jpg") stbi_write_jpg(path.c_str(), width, height, 4, pixels, 80);
            else if (extension == "bmp") stbi_write_bmp(path.c_str(), width, height, 4, pixels);
            else throw std::runtime_error("Unknown file extension.");
        }

        // close the instance
        ImGuiFileDialog::Instance()->Close();
    }

    // render the GUI
    ImGui::Render(), ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
