#pragma once

#include <string>
#include <vector>

struct Texture {
    unsigned int id;
    std::string name;
    std::string path;
};

class Mesh {
public:
    Mesh(std::vector<float>& vertices, std::vector<Texture>& textures);

    // render the mesh
    void render();

private:
    // initializes all the buffer objects/arrays
    void setup();

    // mesh Data
    std::vector<float> m_vertices;
    std::vector<Texture> m_textures;

    unsigned int m_VAO{};
    unsigned int m_VBO{};


};