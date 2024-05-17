#include "shader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

#define CHECK_ERR(ivFunc, status, infoLogFunc, errstr) {                \
    ivFunc(shader, status, &success);                                   \
    if (!success) {                                                     \
        glDeleteShader(shader);                                         \
        infoLogFunc(shader, 1024, nullptr, infoLog);                    \
        throw std::runtime_error(std::string(errstr) + "\n" + infoLog); \
    }                                                                   \
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        throw std::runtime_error(std::string("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: ") + e.what());
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    // vertex shader
    vertex = createShader(&vShaderCode, GL_VERTEX_SHADER);

    // fragment Shader
    fragment = createShader(&fShaderCode, GL_FRAGMENT_SHADER);

    // shader Program
    mID = glCreateProgram();
    glAttachShader(mID, vertex);
    glAttachShader(mID, fragment);
    glLinkProgram(mID);

    checkErrors(mID, ErrorType::LINKING);

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(mID);
}

void Shader::activate() const {
    glUseProgram(mID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(mID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(mID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::createShader(const char** source, GLuint type) {
    unsigned int shader = glCreateShader(type);

    glShaderSource(shader, 1, source, nullptr);
    glCompileShader(shader);

    checkErrors(shader, ErrorType::COMPILE);

    return shader;
}

void Shader::checkErrors(GLuint shader, ErrorType type) {
    GLint success;
    char infoLog[1024];

    if (type == ErrorType::COMPILE) {
        CHECK_ERR(glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog, "ERROR::SHADER_COMPILATION_ERROR:")
    } else {
        CHECK_ERR(glGetProgramiv, GL_LINK_STATUS, glGetProgramInfoLog, "ERROR::PROGRAM_LINKING_ERROR:")
    }
}









