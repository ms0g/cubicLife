#include "skybox.h"

Skybox::Skybox() :
        m_shader(std::make_unique<Shader>(fs::path(SHADER_DIR + "skybox.vert.glsl"),
                                          fs::path(SHADER_DIR + "skybox.frag.glsl"))) {

    m_shader->activate();
    m_shader->setInt(m_textures[0].name, 0);

    m_mesh = std::make_unique<SkyboxMesh>(m_vertices, m_textures);
    m_mesh->setup();
}

void Skybox::draw() {
    m_mesh->render();
}

void Skybox::updateViewMatrix(glm::mat4 view) {
    m_shader->activate();
    m_shader->setMat4("view", view);
}

void Skybox::updateProjectionMatrix(glm::mat4 projection) {
    m_shader->activate();
    m_shader->setMat4("projection", projection);
}


