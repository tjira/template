#include "shader.h"

Shader::Shader(const std::string& vertex, const std::string& fragment) : id(glCreateProgram()) {
    // extract the C strings from the input string
    const char *fsCode = fragment.c_str(), *vsCode = vertex.c_str();

    // create the vertex and fragment shader
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);

    // set the sources
    glShaderSource(vs, 1, &vsCode, nullptr);
    glShaderSource(fs, 1, &fsCode, nullptr);

    // compile both shaders
    glCompileShader(vs), glCompileShader(fs);

    // chack for errors
    lint(vs, "vertex"), lint(fs, "fragment");

    // attach shaders to program, link and validate
    glAttachShader(id, vs), glAttachShader(id, fs);
    glLinkProgram(id), glValidateProgram(id);

    // detach and delete vertex and fragment shaders
    glDetachShader(id, vs), glDetachShader(id, fs);
    glDeleteShader(vs), glDeleteShader(fs), use();
}

void Shader::lint(unsigned int shader, const std::string& title) const {
    // declate status and length
    int success, length; std::vector<char> log;

    // extract status and length
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    // get the compile log
    log.resize(length); glGetShaderInfoLog(shader, length, &length, &log[0]);

    // throw an error
    if(!success) throw std::runtime_error(title + ": " + std::string(log.begin(), log.end()));
}
