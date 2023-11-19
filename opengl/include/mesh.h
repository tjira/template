#pragma once

#include "buffer.h"
#include "shader.h"

class Mesh {
public:
    // constructors
    Mesh(std::vector<Vertex> data, const std::string& name = "mesh") : name(name), model(1.0f), buffer(data) {}
    static Mesh Icosphere(int subdivisions, bool smooth, const std::string& name = "icosphere");
    static Mesh Cube(const std::string& name = "cube");
    // Mesh(const Mesh& mesh) {this->name = mesh.name, this->model = mesh.model, this->buffer = mesh.buffer; std::cout << "mesh assign" << std::endl;}

    // getters and setters
    std::string getName() const {return name;} glm::vec3 getPosition() const {return glm::vec3(model[3]);}
    void setColor(const glm::vec3& color); void setModel(const glm::mat4& model) {this->model = model;}
    void setPosition(const glm::vec3& pos) {setModel(glm::translate(model, pos - getPosition()));}
    void translate(const glm::vec3& dir) {setModel(glm::translate(model, dir));}

    // state functions
    void render(const Shader& shader, const glm::mat4& transform = glm::mat4(1.0f)) const;

private:
    std::string name;
    glm::mat4 model;
    Buffer buffer;
};
