#include "cellMesh.h"

CellMesh::CellMesh(std::vector<float>& vertices, std::vector<Texture>& textures) :
        IMesh(vertices, textures) {}

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // vertex Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 3);
    glEnableVertexAttribArray(1);

    // vertex texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void CellMesh::setupInstancing(std::vector<glm::mat4>& modelMatrices) {
    mModelMatrices = std::move(modelMatrices);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ARRAY_BUFFER, mModelMatrices.size() * sizeof(glm::mat4), &mModelMatrices[0], GL_STATIC_DRAW);

    glBindVertexArray(mVAO);
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

void CellMesh::render() {
    for (unsigned int i = 0; i < mTextures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
    }
    // draw mesh
    glBindVertexArray(mVAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, (int)mModelMatrices.size());
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}


