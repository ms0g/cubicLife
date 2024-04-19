#include "skyboxMesh.h"

SkyboxMesh::SkyboxMesh(std::vector<float>& vertices, std::vector<Texture>& textures) :
        IMesh(vertices, textures) {}

void SkyboxMesh::setup() {
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

void SkyboxMesh::render() {
    for (int i = 0; i < mTextures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_CUBE_MAP, mTextures[i].id);
    }

    // draw mesh
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}


