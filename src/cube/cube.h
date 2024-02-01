#pragma once

#include <vector>
#include "filesystem/filesystem.h"
#include "../configs/configs.hpp"
#include "../mesh/mesh.h"
#include "../mesh/texture.h"

class Shader;
class Cube {
public:
    explicit Cube(Shader& shader);

    void draw();

private:
    Mesh mesh;
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
