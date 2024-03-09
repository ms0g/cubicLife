#pragma once

#include <vector>
#include <memory>
#include "filesystem/filesystem.h"
#include "mesh/cubeMesh.h"
#include "mesh/texture.h"
#include "../configs/configs.hpp"
#include "../shader/shader.h"

class Cube {
public:
    explicit Cube(std::vector<glm::mat4>& modelMatrices);

    void update(glm::mat4 view, glm::mat4 projection);

    void draw();

private:
    std::unique_ptr<CubeMesh> m_mesh;
    std::unique_ptr<Shader> m_shader;
#define TEX1 0.0
#define TEX2 1.0
    std::vector<float> m_vertices = {
            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, TEX1, // Bottom-left
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, TEX1, // top-right
             0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, TEX1, // top-right
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, TEX1, // bottom-left
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f, TEX1, // top-left
            // Front face
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f, TEX1, // bottom-left
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f, TEX1, // top-right
             0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f, TEX1, // top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 1.0f, TEX1, // top-left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f, TEX1, // bottom-left
            // Left face
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, TEX1, // top-right
            -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, TEX1, // top-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, TEX1, // bottom-left
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, TEX1, // bottom-left
            -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, TEX1, // bottom-right
            -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, TEX1, // top-right
            // Right face
             0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, TEX1, // top-left
             0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f, TEX1, // top-right
             0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, TEX1, // top-left
             0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, TEX1, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, TEX2, // top-right
             0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 1.0f, TEX2, // top-left
             0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f, TEX2, // bottom-left
             0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f, TEX2, // bottom-left
            -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, TEX2, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f, TEX2, // top-right
            // Top face
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, TEX2, // top-left
             0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f, TEX2, // bottom-right
             0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f, TEX2, // top-right
             0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f, TEX2, // bottom-right
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, TEX2, // top-left
            -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, TEX2, // bottom-left
    };

    std::vector<Texture> m_textures = {
            {texture::load(fs::path(ASSET_DIR + "grass.png").c_str()),
                    "tex.texture1",
                    "grass.png"},
            {texture::load(fs::path(ASSET_DIR + "grass_top.png").c_str()),
                    "tex.texture2",
                    "grass_top.png"}
    };
};
