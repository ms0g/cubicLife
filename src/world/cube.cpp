#include "cube.h"

Cube::Cube(std::vector<glm::mat4>& modelMatrices) :
        m_shader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cube.vert.glsl"),
                                          fs::path(SHADER_DIR + "cube.frag.glsl"))) {
    m_shader->activate();
    for (int i = 0; i < m_textures.size(); ++i) {
        m_shader->setInt(m_textures[i].name, i);
    }

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
