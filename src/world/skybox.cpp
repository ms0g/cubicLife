#include "skybox.h"
#include "mesh/skyboxMesh.h"
#include "../shader/shader.h"

Skybox::Skybox() {
    mMesh = std::make_unique<SkyboxMesh>(mVertices, mTextures);
    mMesh->setup();

    mShader = std::make_unique<Shader>(fs::path(SHADER_DIR + "skybox.vert.glsl"),
                                       fs::path(SHADER_DIR + "skybox.frag.glsl"));
    mShader->activate();
    mShader->setInt(mTextures[0].name, 0);
}

Skybox::~Skybox() = default;

void Skybox::draw(glm::mat4 view, glm::mat4 projection) {
    mShader->activate();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    mMesh->render();
}




