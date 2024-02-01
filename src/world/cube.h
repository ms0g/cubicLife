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
    Cube();

    void draw();

    void updateViewMatrix(glm::mat4 view);

    void updateModelMatrix(glm::mat4 model);

    void updateProjectionMatrix(glm::mat4 projection);

private:
    std::unique_ptr<Mesh> m_mesh;
    std::unique_ptr<Shader> m_shader;
#define TEX1 0.0
#define TEX2 1.0
    std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, TEX1,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, TEX1,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, TEX1,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, TEX1,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, TEX1,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, TEX1,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, TEX1,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, TEX1,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, TEX1,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, TEX1,

            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, TEX1,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, TEX1,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1,
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, TEX1,
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, TEX1,

            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, TEX1,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, TEX1,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, TEX1,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, TEX1,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, TEX1,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, TEX2,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, TEX2,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, TEX2,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, TEX2,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, TEX2,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, TEX2,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, TEX2,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, TEX2,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, TEX2,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, TEX2,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, TEX2,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, TEX2,
    };

    std::vector<Texture> textures = {
            {texture::load(fs::path(ASSET_DIR + "grass.png").c_str()),
                    "texture1",
                    "grass.png"},
            {texture::load(fs::path(ASSET_DIR + "grass_top.png").c_str()),
                    "texture2",
                    "grass_top.png"}
    };
};
