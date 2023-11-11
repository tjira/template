#include "buffer.h"

Buffer::~Buffer() {
    glDeleteVertexArrays(1, &vao), glDeleteBuffers(1, &vbo);
};

Buffer& Buffer::operator=(const Buffer& buffer) {
    // delete the current buffers
    glDeleteVertexArrays(1, &vao), glDeleteBuffers(1, &vbo);

    // assign data to this buffer and generate
    this->data = buffer.data, generate();

    // return new buffer
    return *this;
}

void Buffer::bind() const {
    glBindVertexArray(vao);
}

void Buffer::generate() {
    // generate and bind buffers
    glGenVertexArrays(1, &vao), glGenBuffers(1, &vbo), glBindBuffer(GL_ARRAY_BUFFER, vbo), glBindVertexArray(vao);

    // set attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // enable atribute pointers
    glEnableVertexAttribArray(0), glEnableVertexAttribArray(1), glEnableVertexAttribArray(2);

    // set buffer data
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
}
