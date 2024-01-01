#pragma once

#include "opengl.h"

class Shader {
public:
    // constructors and destructors
    ~Shader() {glDeleteProgram(id);} Shader(const std::string& vertex, const std::string& fragment);

    // setters
    template <typename T> void set(const std::string& name, T value) const;

    // state functions
    void use() const {glUseProgram(id);}

private:
    void lint(unsigned int shader, const std::string& title) const;
    unsigned int id;
};

template <typename T>
void Shader::set(const std::string& name, T value) const {
    if constexpr (std::is_same<T, int>()) glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    else if constexpr (std::is_same<T, float>()) glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    else if constexpr (std::is_same<T, glm::vec3>()) glUniform3f(glGetUniformLocation(id, name.c_str()), value[0], value[1], value[2]);
    else if constexpr (std::is_same<T, glm::vec4>()) glUniform4f(glGetUniformLocation(id, name.c_str()), value[0], value[1], value[2], value[3]);
    else if constexpr (std::is_same<T, glm::mat4>()) glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    else throw std::runtime_error("INVALID TYPE IN SHADER VARIABLE SETTER");
}
