#include "material.h"

Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess) {
    this->ambient = ambient; this->diffuse = diffuse; this->specular = specular; this->shininess = shininess;
}
