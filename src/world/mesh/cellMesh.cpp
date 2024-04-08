#include "cellMesh.h"
#include <utility>
#include "glad/glad.h"

CellMesh::CellMesh(std::vector<float>& vertices) :
        IMesh(vertices) {}

void CellMesh::setup() {
    // create vao
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // create buffers
    glGenBuffers(1, &m_VBO);

    // bind the buffer to be used
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), &mVertices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers

    // vertex Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void CellMesh::render() {
    // draw mesh
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

}


