#pragma once

#include <glm/glm.hpp>
#include <algorithm>
#include <vector>

struct Vertex {
    glm::vec3 position, normal = glm::vec3(0), color = glm::vec3(1);
};

#include <glm/gtc/matrix_transform.hpp>
