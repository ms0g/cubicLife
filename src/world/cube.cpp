#include "cube.h"
#include "mesh/cubeMesh.h"
#include "../shader/shader.h"

Cube::Cube(std::vector<glm::mat4>& modelMatrices) :
        mShader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cube.vert.glsl"),
                                         fs::path(SHADER_DIR + "cube.frag.glsl"))) {
    mShader->activate();
    for (int i = 0; i < mTextures.size(); ++i) {
        mShader->setInt(mTextures[i].name, i);
    }

    mMesh = std::make_unique<CubeMesh>(mVertices, mTextures, modelMatrices);
    mMesh->setup();
    mMesh->setupInstancing();
}

Cube::~Cube() = default;

void Cube::update(glm::mat4 view, glm::mat4 projection) {
    mShader->activate();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);
}

void Cube::draw() {
    mMesh->render();
}
