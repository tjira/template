#pragma once

#include "opengl.h"

class Buffer {
public:
    // constructors
    Buffer(const Buffer& buffer) : data(buffer.getData()) {generate();}
    Buffer(const std::vector<Vertex>& data) : data(data) {generate();}

    // empty constructor and destructor
    Buffer() : data(0) {generate();} ~Buffer();

    // getters
    std::vector<Vertex> getData() const {return data;}
    size_t getSize() const {return data.size();}

    // state functions
    void bind() const {glBindVertexArray(vao);}

private:
    std::vector<Vertex> data;
    unsigned int vao, vbo;
    void generate();
};
