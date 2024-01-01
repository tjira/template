#pragma once

#include "opengl.h"

class Material {
public:
    // constructors
    Material() = default; Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);

    // getters
    glm::vec3 getSpecular() const {return specular;}
    glm::vec3 getAmbient() const {return ambient;}
    glm::vec3 getDiffuse() const {return diffuse;}
    float getShininess() const {return shininess;}

private:
    glm::vec3 ambient = {1.0f, 1.0f, 1.0f}, diffuse = {1.0f, 1.0f, 1.0f}, specular = {1.0f, 1.0f, 1.0f}; float shininess = 4.0f;
};
