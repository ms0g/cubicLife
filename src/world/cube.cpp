#include "cube.h"
#include "mesh/cubeMesh.h"
#include "filesystem/filesystem.h"
#include "../configs/configs.hpp"
#include "../shader/shader.h"

Cube::Cube() : mShader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cube.vert.glsl"),
                                                fs::path(SHADER_DIR + "cube.frag.glsl"))) {

    mMesh = std::make_unique<CubeMesh>(mVertices);
    mMesh->setup();
}

Cube::~Cube() = default;

void Cube::update(glm::mat4 view, glm::mat4 modelMat, glm::mat4 projection) {
    mShader->activate();
    mShader->setMat4("view", view);
    mShader->setMat4("model", modelMat);
    mShader->setMat4("projection", projection);
}

void Cube::draw() {
    mMesh->render();
}
