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

    void draw();

    void updateViewMatrix(glm::mat4 view);

    void updateProjectionMatrix(glm::mat4 projection);
private:
    std::unique_ptr<SkyboxMesh> m_mesh;
    std::unique_ptr<Shader> m_shader;

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

};

