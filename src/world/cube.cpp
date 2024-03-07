#include "cube.h"

Cube::Cube(std::vector<glm::mat4>& modelMatrices) :
        m_shader(std::make_unique<Shader>(fs::path(SHADER_DIR + "cube.vert.glsl"),
                                          fs::path(SHADER_DIR + "cube.frag.glsl"))) {
    m_shader->activate();
    m_shader->setInt(m_textures[0].name, 0);
    m_shader->setInt(m_textures[1].name, 1);

    m_shader->setVec3("light.direction", 0.0f, -50.0f, -20.0f);
    // light properties
    m_shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    m_shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    m_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    m_mesh = std::make_unique<CubeMesh>(m_vertices, m_textures, modelMatrices);
    m_mesh->setup();
    m_mesh->setupInstancing();
}

void Cube::update(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos) {
    m_shader->activate();
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
    m_shader->setVec3("viewPos", cameraPos);
}

void Cube::draw() {
    m_mesh->render();
}
