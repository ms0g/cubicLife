#include "mesh.h"
#include <utility>
#include "glad/glad.h"

Mesh::Mesh(std::vector<float>& vertices, std::vector<Texture>& textures, std::vector<glm::mat4>& modelMatrices) :
        m_vertices(std::move(vertices)),
        m_textures(std::move(textures)),
        m_modelMatrices(std::move(modelMatrices)){
    setup();
    setupInstancing();
}

void Mesh::render() {
    for (unsigned int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    // draw mesh
    glBindVertexArray(m_VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, m_modelMatrices.size());
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}


void Mesh::setup() {
    // create vao
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // create buffers
    glGenBuffers(1, &m_VBO);

    // bind the buffer to be used
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers

    // vertex Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // vertex texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // vertex texture type
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::setupInstancing() {
    glGenBuffers(1, &m_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, m_modelMatrices.size() * sizeof(glm::mat4), &m_modelMatrices[0], GL_STATIC_DRAW);

    glBindVertexArray(m_VAO);
    // set attribute pointers for matrix (4 times vec4)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) 0);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) (sizeof(glm::vec4)));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) (2 * sizeof(glm::vec4)));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) (3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}
