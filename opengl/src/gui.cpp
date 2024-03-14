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

void Gui::render(Scene& scene) {
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
        ImGui::DragFloat3("Ambient", &pointer->light.ambient[0], 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Diffuse", &pointer->light.diffuse[0], 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Specular", &pointer->light.specular[0], 0.01f, 0.0f, 1.0f);

        // end the window
        ImGui::End();
    }

    // objects window
    if (pointer->flags.objects) {
        // begin the window
        ImGui::Begin("Objects", &pointer->flags.objects, ImGuiWindowFlags_AlwaysAutoResize);

        // begin the table
        if (ImGui::BeginTable("##split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_ScrollY)) {
            // setupt cable columns
            ImGui::TableSetupColumn("Object");
            ImGui::TableSetupColumn("Values");
            ImGui::TableHeadersRow();

            // display all objects
            for (Mesh& mesh : scene.get()) {
                // push ID, get to the next row and select first column
                ImGui::PushID(&mesh), ImGui::TableNextRow(), ImGui::TableSetColumnIndex(0);

                // display the object tree
                if (ImGui::TreeNode("Object", "%s_%u", mesh.getName().c_str(), (unsigned int)(uintptr_t)(&mesh))) {

                    // extract all the properties
                    glm::vec3 position = mesh.getPosition();

                    // add row and select first column
                    ImGui::TableNextRow(), ImGui::TableSetColumnIndex(0), ImGui::AlignTextToFramePadding();

                    // print the property name
                    ImGui::Text("Position");

                    // select the second row and its width
                    ImGui::TableSetColumnIndex(1), ImGui::PushItemWidth(200);

                    // create the property slider
                    if (ImGui::DragFloat3("", &position[0], 0.01f, -10.0f, 10.0f)) mesh.setPosition(position);

                    // pop tree ID
                    ImGui::TreePop();
                }

                // pop mesh id
                ImGui::PopID();
            }

            // end the table
            ImGui::EndTable();
        }

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

    // if opening obj file open the window
    if (ImGuiFileDialog::Instance()->Display("Open Model", ImGuiWindowFlags_NoCollapse, {512, 288})) {
        // if the image save is confirmed
        if (ImGuiFileDialog::Instance()->IsOk()) {
            // add model to the scene
            scene.add(Mesh::Load(ImGuiFileDialog::Instance()->GetFilePathName()), {0, 0, 0});
        }

        // close the instance
        ImGuiFileDialog::Instance()->Close();
    }

    // if saving the screenshot open the window
    if (ImGuiFileDialog::Instance()->Display("Save Screenshot", ImGuiWindowFlags_NoCollapse, {512, 288})) {
        // get the with and height of the viewport and create pixel array
        GLint viewport[4]; glGetIntegerv(GL_VIEWPORT, viewport);
        int width = viewport[2], height = viewport[3];

        // create the vector of pixels
        std::vector<unsigned char> pixels(4 * width * height);

        // read the buffer
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

        // if the image save is confirmed
        if (ImGuiFileDialog::Instance()->IsOk()) {
            // get the path and extension
            std::string path = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string extension = path.substr(path.find_last_of(".") + 1);

            // flip the image
            for (int i = 0; i < 4 * width; i++) {
                for (int j = 0; j < height / 2; j++) {
                    std::swap(pixels.at(4 * j * width + i), pixels.at(4 * (height - j - 1) * width + i));
                }
            }

            // save the buffer
            if (extension == "png") stbi_write_png(path.c_str(), width, height, 4, pixels.data(), 4 * width);
            else if (extension == "jpg") stbi_write_jpg(path.c_str(), width, height, 4, pixels.data(), 80);
            else if (extension == "bmp") stbi_write_bmp(path.c_str(), width, height, 4, pixels.data());
            else throw std::runtime_error("Unknown file extension.");
        }

        // close the instance
        ImGuiFileDialog::Instance()->Close();
    }

    // render the GUI
    ImGui::Render(), ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
