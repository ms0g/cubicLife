#include "cube.h"

Cube::Cube(std::vector<glm::mat4>& modelMatrices) :
        m_shader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cube.vert.glsl"),
                                          fs::path(SHADER_DIR + "cube.frag.glsl"))) {
    m_shader->activate();
    m_shader->setInt(m_textures[0].name, 0);
    m_shader->setInt(m_textures[1].name, 1);

    m_mesh = std::make_unique<CubeMesh>(m_vertices, m_textures, modelMatrices);
    m_mesh->setup();
    m_mesh->setupInstancing();
}

void Cube::update(glm::mat4 view, glm::mat4 projection) {
    m_shader->activate();
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
}

void Cube::draw() {
    m_mesh->render();
}
