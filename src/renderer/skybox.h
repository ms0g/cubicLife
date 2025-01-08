#pragma once

#include <vector>
#include <string>
#include <memory>
#include "glm/glm.hpp"
#include "mesh/texture.h"
#include "../config/config.hpp"
#include "../core/io.hpp"

class Shader;
class SkyboxMesh;
class Skybox {
public:
    Skybox();

    ~Skybox();

    void render(glm::mat4 view, glm::mat4 projection);

private:
    std::unique_ptr<SkyboxMesh> mMesh;
    std::unique_ptr<Shader> mShader;

    std::vector<float> mVertices = {
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

    std::vector<std::string> mFaces = {
            fs::path(ASSET_DIR + "/skybox/right.jpg"),
            fs::path(ASSET_DIR + "/skybox/left.jpg"),
            fs::path(ASSET_DIR + "/skybox/top.jpg"),
            fs::path(ASSET_DIR + "/skybox/bottom.jpg"),
            fs::path(ASSET_DIR + "/skybox/front.jpg"),
            fs::path(ASSET_DIR + "/skybox/back.jpg")
    };

    std::vector<Texture> mTextures = {
            {texture::loadCubemap(mFaces), "skybox", "skybox.jpg"}
    };
};

