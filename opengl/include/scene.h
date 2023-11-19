#pragma once

#include "mesh.h"

class Scene {
public:
    // constructors and destructors
    Scene() = default; ~Scene() = default;

    // setters and getters
    void add(const Mesh& mesh, const glm::vec3& pos = {0, 0, 0}) {meshes.push_back(mesh), meshes.at(meshes.size() - 1).setPosition(pos);}
    std::vector<Mesh>& get() {return meshes;}

    // state functions
    void render(const Shader& shader, const glm::mat4& transform = glm::mat4(1.0f)) const;

private:
    std::vector<Mesh> meshes;
};
