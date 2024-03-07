#pragma once

#include <vector>
#include "mesh/skyboxMesh.h"
#include "mesh/texture.h"
#include "filesystem/filesystem.h"
#include "../configs/configs.hpp"
#include "../shader/shader.h"

class Skybox {
public:
    Skybox();

    void update(glm::mat4 view, glm::mat4 projection);

    void draw();

private:
    std::unique_ptr<SkyboxMesh> m_mesh;
    std::unique_ptr<Shader> m_shader;

    std::vector<float> m_vertices = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
    };

    std::vector<std::string> m_faces = {
            fs::path(ASSET_DIR + "skybox/right.jpg"),
            fs::path(ASSET_DIR + "skybox/left.jpg"),
            fs::path(ASSET_DIR + "skybox/top.jpg"),
            fs::path(ASSET_DIR + "skybox/bottom.jpg"),
            fs::path(ASSET_DIR + "skybox/front.jpg"),
            fs::path(ASSET_DIR + "skybox/back.jpg")
    };

    std::vector<Texture> m_textures = {
            {texture::loadCubemap(m_faces), "skybox", "skybox.jpg"}
    };
};

