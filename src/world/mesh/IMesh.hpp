//
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

    void setup() {
        setupImpl();
    }

    void render() {
        renderImpl();
    }

protected:
    // render the mesh
    virtual void renderImpl() = 0;

    virtual void setupImpl() = 0;

    unsigned int m_VAO{};
    unsigned int m_VBO{};
    // mesh Data
    std::vector<float> m_vertices;
    std::vector<Texture> m_textures;
};
