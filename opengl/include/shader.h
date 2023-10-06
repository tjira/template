#pragma once

#include "opengl.h"
#include "vertex.h"

class Shader {
public:
    // constructors and destructors
    ~Shader(); Shader(const std::string& vertex, const std::string& fragment);

    // setters
    template <typename T> void set(const std::string& name, T value) const;

    // state functions
    void use() const;

private:
    void errorCheck(unsigned int shader, const std::string& title) const;
    unsigned int id;
};
