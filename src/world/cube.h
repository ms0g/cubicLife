#pragma once

#include <vector>
#include <memory>
#include "filesystem/filesystem.h"
#include "mesh/mesh.h"
#include "mesh/texture.h"
#include "../configs/configs.hpp"
#include "../shader/shader.h"

class Cube {
public:
    explicit Cube(std::vector<glm::mat4>& modelMatrices);

    void draw();

    void updateViewMatrix(glm::mat4 view);

    void updateProjectionMatrix(glm::mat4 projection);

private:
    std::unique_ptr<Mesh> m_mesh;
    std::unique_ptr<Shader> m_shader;
#define TEX1 0.0
#define TEX2 1.0
    std::vector<float> m_vertices = {
            // Back face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1, // Bottom-left
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, TEX1, // top-right
             0.5f, -0.5f, -0.5f, 1.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, TEX1, // top-right
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1, // bottom-left
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, TEX1, // top-left
            // Front face
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, TEX1, // bottom-left
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, TEX1, // top-right
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, TEX1, // top-right
            -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, TEX1, // top-left
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, TEX1, // bottom-left
            // Left face
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, TEX1, // top-right
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, TEX1, // top-left
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1, // bottom-left
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1, // bottom-left
            -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, TEX1, // bottom-right
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, TEX1, // top-right
            // Right face
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, TEX1, // top-left
             0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f, -0.5f, 0.0f, 1.0f, TEX1, // top-right
             0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1, // bottom-right
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, TEX1, // top-left
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f, TEX1, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, TEX2, // top-right
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, TEX2, // top-left
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f, TEX2, // bottom-left
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f, TEX2, // bottom-left
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, TEX2, // bottom-right
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, TEX2, // top-right
            // Top face
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, TEX2, // top-left
             0.5f,  0.5f,  0.5f, 1.0f, 0.0f, TEX2, // bottom-right
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, TEX2, // top-right
             0.5f,  0.5f,  0.5f, 1.0f, 0.0f, TEX2, // bottom-right
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, TEX2, // top-left
            -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, TEX2, // bottom-left
    };

    std::vector<Texture> m_textures = {
            {texture::load(fs::path(ASSET_DIR + "grass.png").c_str()),
                    "texture1",
                    "grass.png"},
            {texture::load(fs::path(ASSET_DIR + "grass_top.png").c_str()),
                    "texture2",
                    "grass_top.png"}
    };
};
