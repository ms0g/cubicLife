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

void CellMesh::setupInstancing(std::vector<glm::mat4>& modelMatrices) {
    mModelMatrices = std::move(modelMatrices);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ARRAY_BUFFER, mModelMatrices.size() * sizeof(glm::mat4), &mModelMatrices[0], GL_STATIC_DRAW);

    glBindVertexArray(mVAO);
    // set attribute pointers for matrix (4 times vec4)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) 0);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) (sizeof(glm::vec4)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) (2 * sizeof(glm::vec4)));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*) (3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);
}

void CellMesh::render() {
    // draw mesh
    glBindVertexArray(mVAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, mModelMatrices.size());
    glBindVertexArray(0);

}


