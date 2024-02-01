#include "cube.h"

Cube::Cube() :
        m_shader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cube.vert.glsl"),
                                          fs::path(SHADER_DIR + "cube.frag.glsl"))) {
    m_shader->activate();
    m_shader->setInt(textures[0].name, 0);
    m_shader->setInt(textures[1].name, 1);

    m_mesh = std::make_unique<Mesh>(vertices, textures);
}

void Cube::updateViewMatrix(glm::mat4 view) {
    m_shader->activate();
    m_shader->setMat4("view", view);
}

void Cube::updateModelMatrix(glm::mat4 model) {
    m_shader->activate();
    m_shader->setMat4("model", model);
}

void Cube::updateProjectionMatrix(glm::mat4 projection) {
    m_shader->activate();
    m_shader->setMat4("projection", projection);
}

void Cube::draw() {
    m_mesh->render();
}
