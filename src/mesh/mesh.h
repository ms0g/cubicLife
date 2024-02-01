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
    Mesh() = default;

    void setup(std::vector<float>& vertices, std::vector<Texture>& textures);
    // render the mesh
    void render();

private:
    // initializes all the buffer objects/arrays

    // mesh Data
    std::vector<Texture> m_textures;
    unsigned int m_VAO{};
    unsigned int m_VBO{};


};