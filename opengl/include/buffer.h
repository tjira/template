#pragma once

#include "opengl.h"
#include "vertex.h"

class Buffer {
public:
    // constructors and destructors
    Buffer(const Buffer& buffer) : data(buffer.getData()) {generate();};
    Buffer(const std::vector<Vertex>& data) : data(data) {generate();};
    Buffer() : data(0) {generate();}; ~Buffer();

    // operators
    Buffer& operator=(const Buffer& buffer);

    // getters
    std::vector<Vertex> getData() const {return data;}
    size_t getSize() const {return data.size();};

    // state functions
    void bind() const;

private:
    std::vector<Vertex> data;
    unsigned int vao, vbo;
    void generate();
};
