#include "callback.h"
#include "mesh.h"
#include "parser.h"
#include "gui.h"

std::string vertex = R"(
#version 420 core

// locations in the buffer
layout(location = 0) in vec3 i_position;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec3 i_color;

// input variables
uniform mat4 u_model, u_view, u_proj;

// output variables
out vec3 fragment, normal, color; out mat3 transform;

void main() {
    normal = normalize(mat3(transpose(inverse(u_model))) * i_normal);
    fragment = vec3(u_model * vec4(i_position, 1)), color = i_color;
    gl_Position = u_proj * u_view * vec4(fragment, 1);
    transform = inverse(mat3(u_view));
})";

std::string fragment = R"(
#version 420 core

// create the light struct
struct Light {vec3 position; float ambient, diffuse, specular, shininess;};

// input variables
uniform Light u_light; uniform vec3 u_camera;

// passed variables
in vec3 fragment, normal, color; in mat3 transform;

// output variables
out vec4 o_color;

void main() {
    vec3 lightPos = transform * u_light.position, reflection = reflect(-normalize(lightPos), normal), direction = normalize(u_camera - fragment);
    vec3 specular = vec3(pow(max(dot(direction, reflection), 0), u_light.shininess)), diffuse = vec3(max(dot(normal, normalize(lightPos)), 0));
    o_color = vec4((vec3(u_light.ambient) + u_light.diffuse * diffuse + u_light.specular * specular), 1) * vec4(color, 1);
})";

void set(const Shader& shader, const Pointer::Camera& camera, const Pointer::Light& light) {
    shader.set<glm::vec3>("u_camera", -glm::inverse(glm::mat3(camera.view)) * glm::vec3(camera.view[3]));
    shader.set<glm::mat4>("u_view", camera.view);
    shader.set<glm::mat4>("u_proj", camera.proj);
    shader.set<glm::vec3>("u_light.position", light.position);
    shader.set<float>("u_light.shininess", light.shininess);
    shader.set<float>("u_light.specular", light.specular);
    shader.set<float>("u_light.ambient", light.ambient);
    shader.set<float>("u_light.diffuse", light.diffuse);
}

int main(int argc, char** argv) {
    // initialize the argument parser
    Parser parser(argc, argv);

    // Initialize GLFW and throw error if failed
    if(!glfwInit()) {
        throw std::runtime_error("Error during GLFW initialization.");
    }

    // declare GLFW pointer
    Pointer pointer; 

    // pass OpenGL version and other hints
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, pointer.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, pointer.minor);
    glfwWindowHint(GLFW_SAMPLES, pointer.samples);

    // create the window
    if (pointer.window = glfwCreateWindow(pointer.width, pointer.height, pointer.title, nullptr, nullptr); !pointer.window) {
        throw std::runtime_error("Error during window creation.");
    }

    // Initialize GLAD
    if (glfwMakeContextCurrent(pointer.window); !gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("Error during GLAD initialization.");
    }

    // assign pointer and enable depth test and culling
    glfwSetWindowUserPointer(pointer.window, &pointer);
    glEnable(GL_DEPTH_TEST), glEnable(GL_CULL_FACE);

    // enable VSync
    glfwSwapInterval(1);

    // set event callbacks
    glfwSetCursorPosCallback(pointer.window, positionCallback);
    glfwSetWindowSizeCallback(pointer.window, resizeCallback);
    glfwSetScrollCallback(pointer.window, scrollCallback);
    glfwSetKeyCallback(pointer.window, keyCallback);

    // initialize camera matrices
    pointer.camera.proj = glm::perspective(glm::radians(45.0f), (float)pointer.width / pointer.height, 0.01f, 1000.0f);
    pointer.camera.view = glm::lookAt({0.0f, 0.0f, 5.0f}, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    {
        // initialize meshes, shaders and GUIs
        auto mesh = Mesh::Icosphere(3, false); 
        Shader shader(vertex, fragment);
        Gui gui(pointer.window);

        // enter the render loop
        while (!glfwWindowShouldClose(pointer.window)) {

            // clear the color and depth buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // set shader variables
            shader.use(), set(shader, pointer.camera, pointer.light);

            // render the mesh and GUI
            mesh.render(shader), gui.render();
            
            // swap buffers and poll events
            glfwSwapBuffers(pointer.window), glfwPollEvents();
        }
    }

    // clean up generated meshes and terminate GLFW
    glfwTerminate();
}
