#include "callback.h"
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
out vec3 fragment, normal, color;

void main() {
    // normal and fragment vectors
    normal = normalize(mat3(transpose(inverse(u_model))) * i_normal);
    fragment = vec3(u_model * vec4(i_position, 1.0));

    // color vector
    color = i_color;

    // output vector
    gl_Position = u_proj * u_view * vec4(fragment, 1);
})";

std::string fragment = R"(
#version 420 core

// create the structures
struct Material {vec3 ambient, diffuse, specular; float shininess;};
struct Light {vec3 position, ambient, diffuse, specular;};

// input variables
uniform Light u_light; uniform Material u_mat; uniform vec3 u_camera;

// passed variables
in vec3 fragment, normal, color;

// output variables
out vec4 o_color;

void main() {
    // calculate the necessary vectors
    vec3 dirLight = normalize(u_light.position - fragment);
    vec3 dirCamera = normalize(u_camera - fragment);
    vec3 dirReflect = reflect(-dirLight, normal);

    // ambient light
    vec3 ambient = u_light.ambient * u_mat.ambient * color;

    // direction of the light and diffuse lighting
    vec3 diffuse = u_light.diffuse * u_mat.diffuse * max(dot(normal, dirLight), 0.0) * color;

    // specular lighting
    vec3 specular = u_light.specular * u_mat.specular * pow(max(dot(dirCamera, dirReflect), 0.0), u_mat.shininess) * color; 

    // output the resulting color
    o_color = vec4(ambient + diffuse + specular, 1.0f);
})";

void set(const Shader& shader, const Pointer::Camera& camera, const Pointer::Light& light) {
    // set the camera position
    shader.set<glm::vec3>("u_camera", -glm::inverse(glm::mat3(camera.view)) * glm::vec3(camera.view[3]));

    // set the view and projection matrices
    shader.set<glm::mat4>("u_view", camera.view);
    shader.set<glm::mat4>("u_proj", camera.proj);

    // set the light position
    shader.set<glm::vec3>("u_light.position", light.position);

    // set the light properties
    shader.set<glm::vec3>("u_light.specular", light.specular);
    shader.set<glm::vec3>("u_light.ambient", light.ambient);
    shader.set<glm::vec3>("u_light.diffuse", light.diffuse);
}

int main(int argc, char** argv) {
    // initialize the argument parser
    Parser parser(argc, argv);

    // Initialize GLFW and throw error if failed
    if(!glfwInit()) {
        throw std::runtime_error("GLFW INITIALIZATION FAILED");
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
        throw std::runtime_error("WINDOW CREATION FAILED");
    }

    // Initialize GLAD
    if (glfwMakeContextCurrent(pointer.window); !gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("GLAD INITIALIZATION FAILED");
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
    pointer.camera.view = glm::lookAt({0.0f, 1.0f, 5.0f}, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    {
        // initialize scene, shader and GUI
        Scene scene; Gui gui(pointer.window);
        Shader shader(vertex, fragment);

        // add light meshes
        scene.add(Mesh::Icosphere(4, false, Material(), "sun"), pointer.light.position);
        scene.add(Mesh::Icosphere(4, false, Material()), {0, 0, 0});

        // enter the render loop
        while (!glfwWindowShouldClose(pointer.window)) {
            // clear the color and depth buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // set shader variables
            shader.use(), set(shader, pointer.camera, pointer.light);

            // render the mesh and GUI
            scene.render(shader), gui.render(scene);
            
            // swap buffers and poll events
            glfwSwapBuffers(pointer.window), glfwPollEvents();
        }
    }

    // terminate GLFW
    glfwTerminate();
}
