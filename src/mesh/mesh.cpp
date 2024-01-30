#include "mesh.h"
#include <utility>
#include "glad/glad.h"
#include "../shader/shader.h"


Mesh::Mesh(std::vector<float>& vertices, std::vector<Texture>& textures) :
        m_vertices(std::move(vertices)),
        m_textures(std::move(textures)) {
    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setup();
}


void Mesh::render() {
    for (unsigned int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    // draw mesh
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // vertex texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}