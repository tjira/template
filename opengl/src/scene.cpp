#include "scene.h"

void Scene::render(const Shader& shader, const glm::mat4& transform) const {
    for (const Mesh& mesh : meshes) mesh.render(shader, transform);
}
