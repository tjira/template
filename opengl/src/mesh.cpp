#include "mesh.h"

#include "tiny_obj_loader.h"

Mesh Mesh::Cube(const Material& mat, const std::string& name) {
    // create the data vector
    std::vector<Vertex> data;

    // fill the data
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f, -0.5f}), glm::vec3{ 0.0f,  0.0f, -1.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f, -0.5f}), glm::vec3{ 0.0f,  0.0f, -1.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f, -0.5f}), glm::vec3{ 0.0f,  0.0f, -1.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f, -0.5f}), glm::vec3{ 0.0f,  0.0f, -1.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f, -0.5f}), glm::vec3{ 0.0f,  0.0f, -1.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f, -0.5f}), glm::vec3{ 0.0f,  0.0f, -1.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f,  0.5f}), glm::vec3{ 0.0f,  0.0f,  1.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f,  0.5f}), glm::vec3{ 0.0f,  0.0f,  1.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f,  0.5f}), glm::vec3{ 0.0f,  0.0f,  1.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f,  0.5f}), glm::vec3{ 0.0f,  0.0f,  1.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f,  0.5f}), glm::vec3{ 0.0f,  0.0f,  1.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f,  0.5f}), glm::vec3{ 0.0f,  0.0f,  1.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f,  0.5f}), glm::vec3{-1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f, -0.5f}), glm::vec3{-1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f, -0.5f}), glm::vec3{-1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f, -0.5f}), glm::vec3{-1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f,  0.5f}), glm::vec3{-1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f,  0.5f}), glm::vec3{-1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f, -0.5f}), glm::vec3{ 1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f,  0.5f}), glm::vec3{ 1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f, -0.5f}), glm::vec3{ 1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f, -0.5f}), glm::vec3{ 1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f,  0.5f}), glm::vec3{ 1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f,  0.5f}), glm::vec3{ 1.0f,  0.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f, -0.5f}), glm::vec3{ 0.0f, -1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f, -0.5f}), glm::vec3{ 0.0f, -1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f,  0.5f}), glm::vec3{ 0.0f, -1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f, -0.5f,  0.5f}), glm::vec3{ 0.0f, -1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f,  0.5f}), glm::vec3{ 0.0f, -1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f, -0.5f, -0.5f}), glm::vec3{ 0.0f, -1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f, -0.5f}), glm::vec3{ 0.0f,  1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f, -0.5f}), glm::vec3{ 0.0f,  1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f,  0.5f}), glm::vec3{ 0.0f,  1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f,  0.5f}), glm::vec3{ 0.0f,  1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{ 0.5f,  0.5f,  0.5f}), glm::vec3{ 0.0f,  1.0f,  0.0f}});
    data.push_back({glm::normalize(glm::vec3{-0.5f,  0.5f, -0.5f}), glm::vec3{ 0.0f,  1.0f,  0.0f}});

    // return the mesh
    return Mesh(data, mat, name);
}

Mesh Mesh::Icosphere(int subdivisions, bool smooth, const Material& mat, const std::string& name) {
    // create the data vector and the icosphere constant
    std::vector<Vertex> data; float k = (1.0f + sqrtf(5.0f)) / 2.0f;

    // triangle #1
    data.push_back({glm::normalize(glm::vec3{-1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{-k,  0,  1})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1,  k})});

    // triangle #2
    data.push_back({glm::normalize(glm::vec3{-1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1,  k})});
    data.push_back({glm::normalize(glm::vec3{ 1,  k,  0})});

    // triangle #3
    data.push_back({glm::normalize(glm::vec3{-1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1, -k})});

    // triangle #4
    data.push_back({glm::normalize(glm::vec3{-1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1, -k})});
    data.push_back({glm::normalize(glm::vec3{-k,  0, -1})});

    // triangle #5
    data.push_back({glm::normalize(glm::vec3{-1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{-k,  0, -1})});
    data.push_back({glm::normalize(glm::vec3{-k,  0,  1})});

    // triangle #6
    data.push_back({glm::normalize(glm::vec3{ 1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1,  k})});
    data.push_back({glm::normalize(glm::vec3{ k,  0,  1})});

    // triangle #7
    data.push_back({glm::normalize(glm::vec3{ 0,  1,  k})});
    data.push_back({glm::normalize(glm::vec3{-k,  0,  1})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1,  k})});

    // triangle #8
    data.push_back({glm::normalize(glm::vec3{-k,  0,  1})});
    data.push_back({glm::normalize(glm::vec3{-k,  0, -1})});
    data.push_back({glm::normalize(glm::vec3{-1, -k,  0})});

    // triangle #9
    data.push_back({glm::normalize(glm::vec3{-k,  0, -1})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1, -k})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1, -k})});

    // triangle #10
    data.push_back({glm::normalize(glm::vec3{ 0,  1, -k})});
    data.push_back({glm::normalize(glm::vec3{ 1,  k,  0})});
    data.push_back({glm::normalize(glm::vec3{ k,  0, -1})});

    // triangle #11
    data.push_back({glm::normalize(glm::vec3{ 0, -1,  k})});
    data.push_back({glm::normalize(glm::vec3{ k,  0,  1})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1,  k})});

    // triangle #12
    data.push_back({glm::normalize(glm::vec3{-1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1,  k})});
    data.push_back({glm::normalize(glm::vec3{-k,  0,  1})});

    // triangle #13
    data.push_back({glm::normalize(glm::vec3{ 0, -1, -k})});
    data.push_back({glm::normalize(glm::vec3{-1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{-k,  0, -1})});

    // triangle #14
    data.push_back({glm::normalize(glm::vec3{ k,  0, -1})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1, -k})});
    data.push_back({glm::normalize(glm::vec3{ 0,  1, -k})});

    // triangle #15
    data.push_back({glm::normalize(glm::vec3{ k,  0,  1})});
    data.push_back({glm::normalize(glm::vec3{ k,  0, -1})});
    data.push_back({glm::normalize(glm::vec3{ 1,  k,  0})});

    // triangle #16
    data.push_back({glm::normalize(glm::vec3{ 1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{ k,  0,  1})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1,  k})});

    // triangle #17
    data.push_back({glm::normalize(glm::vec3{ 1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1,  k})});
    data.push_back({glm::normalize(glm::vec3{-1, -k,  0})});

    // triangle #18
    data.push_back({glm::normalize(glm::vec3{ 1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{-1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1, -k})});

    // triangle #19
    data.push_back({glm::normalize(glm::vec3{ 1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{ 0, -1, -k})});
    data.push_back({glm::normalize(glm::vec3{ k,  0, -1})});

    // triangle #20
    data.push_back({glm::normalize(glm::vec3{ 1, -k,  0})});
    data.push_back({glm::normalize(glm::vec3{ k,  0, -1})});
    data.push_back({glm::normalize(glm::vec3{ k,  0,  1})});

    // subdivide the icosphere
    for (int i = 0; i < subdivisions; i++) {

        // create the container for the subdivided shape
        std::vector<Vertex> subdivided;

        // for every face in the data containner
        for (size_t j = 0; j < data.size(); j += 3) {

            // the end vertices
            glm::vec3 p1 = data.at(j + 0).position;
            glm::vec3 p2 = data.at(j + 1).position;
            glm::vec3 p3 = data.at(j + 2).position;

            // the middle vertices
            glm::vec3 p4 = glm::normalize((p1 + p2) / 2.0f);
            glm::vec3 p5 = glm::normalize((p2 + p3) / 2.0f);
            glm::vec3 p6 = glm::normalize((p3 + p1) / 2.0f);

            // triangle #1
            subdivided.push_back({p1});
            subdivided.push_back({p4});
            subdivided.push_back({p6});

            // triangle #2
            subdivided.push_back({p4});
            subdivided.push_back({p2});
            subdivided.push_back({p5});

            // triangle #3
            subdivided.push_back({p6});
            subdivided.push_back({p5});
            subdivided.push_back({p3});

            // triangle #4
            subdivided.push_back({p4});
            subdivided.push_back({p5});
            subdivided.push_back({p6});
        }

        // assign the subdivided shape to the original
        data = subdivided;
    }

    // assign normals
    for (size_t i = 0; i < data.size(); i += 3) {
        // get two vectors from the same plane
        glm::vec3 v1 = data.at(i + 1).position - data.at(i).position;
        glm::vec3 v2 = data.at(i + 2).position - data.at(i).position;

        // assign the normal vector
        data.at(i + 0).normal = smooth ? data.at(i + 0).position : glm::normalize(glm::cross(v1, v2));
        data.at(i + 1).normal = smooth ? data.at(i + 1).position : glm::normalize(glm::cross(v1, v2));
        data.at(i + 2).normal = smooth ? data.at(i + 2).position : glm::normalize(glm::cross(v1, v2));
    }

    // return the sphere
    return Mesh(data, mat, name);
}

Mesh Mesh::Load(const std::string& filename, const Material& mat, const std::string& name) {
    // check if the file exists
    if (!std::filesystem::exists(filename)) {
        std::cerr << std::string("File '") + filename + std::string("' does not exist.") << std::endl; return Mesh({});
    }

    // prepare the data structures
    std::vector<Vertex> data;
    glm::vec3 center(0.0f);

    // initialize the reader
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(filename)) {
        if (!reader.Error().empty()) {
            throw std::runtime_error(reader.Error());
        }
    }

    // extract references stored in the mesh
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // format the data to my own structure
    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t j = 0, offset = 0; j < shapes[i].mesh.num_face_vertices.size(); j++) {
            for (size_t v = 0; v < shapes[i].mesh.num_face_vertices[j]; v++) {
                Vertex vertex; tinyobj::index_t k = shapes[i].mesh.indices[offset + v];
                vertex.position.x = attrib.vertices[3 * k.vertex_index + 0];
                vertex.position.y = attrib.vertices[3 * k.vertex_index + 1];
                vertex.position.z = attrib.vertices[3 * k.vertex_index + 2];
                if (k.normal_index >= 0) {
                    vertex.normal.x = attrib.normals[3 * k.normal_index + 0];
                    vertex.normal.y = attrib.normals[3 * k.normal_index + 1];
                    vertex.normal.z = attrib.normals[3 * k.normal_index + 2];
                }
                center = center + vertex.position;
                vertex.color = {1, 1, 1};
                data.push_back(vertex);
            }
            offset += shapes[i].mesh.num_face_vertices[j];
        }
    }

    // Center the mesh at the origin
    for (Vertex& vertex : data) {
        vertex.position = vertex.position - center / (float)data.size();
    }

    // Return the object
    return Mesh(data, mat, name);
}

void Mesh::render(const Shader& shader, const glm::mat4& transform) const {
    // use the shader and set the model matrix
    shader.use(), shader.set<glm::mat4>("u_model", transform * model);

    // set material
    shader.set<glm::vec3>("u_mat.specular", material.getSpecular()); shader.set<float>("u_mat.shininess", material.getShininess());
    shader.set<glm::vec3>("u_mat.ambient", material.getAmbient()); shader.set<glm::vec3>("u_mat.diffuse", material.getDiffuse());

    // bind the buffer and draw the vertices
    buffer.bind(), glDrawArrays(GL_TRIANGLES, 0, (int)buffer.getSize());
}

void Mesh::setColor(const glm::vec3& color) {
    // extract the data from the mesh buffer
    std::vector<Vertex> data = buffer.getData();

    // change the color of each vertex
    std::for_each(data.begin(), data.end(), [color](Vertex& v) {v.color = color;});

    // create a new buffer
    buffer = Buffer(data);
}
