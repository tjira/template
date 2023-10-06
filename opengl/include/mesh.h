#pragma once

#include "buffer.h"
#include "shader.h"

class Mesh {
public:
    // constructors
    Mesh(std::vector<Vertex> data, const std::string& name = "mesh") : name(name), model(1.0f), buffer(data) {};

    // static constructors
    static Mesh Icosphere(int subdivisions, bool smooth, const std::string& name = "icosphere");

    // getters
    std::string getName() const; glm::vec3 getPosition() const;

    // setters
    void setColor(const glm::vec3& color);
    void setModel(const glm::mat4& model);

    // state functions
    void render(const Shader& shader, const glm::mat4& transform = glm::mat4(1.0f)) const;

private:
    std::string name;
    glm::mat4 model;
    Buffer buffer;
};
