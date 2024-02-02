#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"

struct Texture {
    unsigned int id;
    std::string name;
    std::string path;
};

class Mesh {
public:
    Mesh(std::vector<float>& vertices, std::vector<Texture>& textures, std::vector<glm::mat4>& modelMatrices);

    // render the mesh
    void render();

private:
    // initializes all the buffer objects/arrays
    void setup();

    void setupInstancing();

    // mesh Data
    std::vector<float> m_vertices;
    std::vector<Texture> m_textures;
    std::vector<glm::mat4> m_modelMatrices;

    unsigned int m_VAO{};
    unsigned int m_VBO{};
    unsigned int m_instanceVBO{};


};