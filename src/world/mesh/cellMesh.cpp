#include "cellMesh.h"
#include "glad/glad.h"

CellMesh::CellMesh(std::vector<float>& vertices) :
        IMesh(vertices) {}

void CellMesh::setup() {
    // create vao
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // create buffers
    glGenBuffers(1, &mVBO);

    // bind the buffer to be used
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), &mVertices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers

    // vertex Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void CellMesh::render() {
    // draw mesh
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

}


