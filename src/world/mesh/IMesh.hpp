#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"

struct Texture {
    unsigned int id;
    std::string name;
    std::string path;
};

class IMesh {
public:
    IMesh(std::vector<float>& vertices, std::vector<Texture>& textures) :
            m_vertices(std::move(vertices)),
            m_textures(std::move(textures)){}

    virtual ~IMesh() = default;

    virtual void setup() = 0;

    virtual void render() = 0;

protected:
    unsigned int m_VAO{};
    unsigned int m_VBO{};
    // mesh Data
    std::vector<float> m_vertices;
    std::vector<Texture> m_textures;
};
