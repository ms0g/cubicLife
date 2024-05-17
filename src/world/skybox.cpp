#include "skybox.h"
#include "mesh/skyboxMesh.h"
#include "../core/shader.h"

Skybox::Skybox() {
    mShader = std::make_unique<Shader>(fs::path(SHADER_DIR + "/skybox.vert.glsl"),
                                       fs::path(SHADER_DIR + "/skybox.frag.glsl"));
    mShader->activate();
    mShader->setInt(mTextures[0].name, 0);

    mMesh = std::make_unique<SkyboxMesh>(mVertices, mTextures);
    mMesh->setup();
}

Skybox::~Skybox() = default;

void Skybox::draw(glm::mat4 view, glm::mat4 projection) {
    mShader->activate();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    mMesh->render();
}




