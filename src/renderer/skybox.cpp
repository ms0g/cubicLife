#include "skybox.h"
#include <string>
#include <vector>
#include "shader.h"
#include "mesh/texture.h"
#include "mesh/skyboxMesh.h"
#include "../config/config.hpp"
#include "../core/io.hpp"

Skybox::Skybox() {
    mShader = std::make_unique<Shader>(fs::path(SHADER_DIR + "/skybox.vert"),
                                       fs::path(SHADER_DIR + "/skybox.frag"));
    std::vector<std::string> faces = {
        fs::path(ASSET_DIR + "/skybox/right.jpg"),
        fs::path(ASSET_DIR + "/skybox/left.jpg"),
        fs::path(ASSET_DIR + "/skybox/top.jpg"),
        fs::path(ASSET_DIR + "/skybox/bottom.jpg"),
        fs::path(ASSET_DIR + "/skybox/front.jpg"),
        fs::path(ASSET_DIR + "/skybox/back.jpg")
    };

    std::vector<Texture> textures = {
        {texture::loadCubemap(faces), "skybox", "skybox.jpg"}
    };

    std::vector<float> vertices = {
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

    mShader->activate();
    mShader->setInt(textures[0].name, 0);

    mMesh = std::make_unique<SkyboxMesh>(vertices, textures);
    mMesh->setup();
}

Skybox::~Skybox() = default;

void Skybox::render(const glm::mat4& view, const glm::mat4& projection) {
    mShader->activate();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    mMesh->render();
}
