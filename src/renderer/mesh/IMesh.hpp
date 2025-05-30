#pragma once

#include <vector>
#include "glad/glad.h"
#include "texture.h"

class IMesh {
public:
    IMesh(std::vector<float>& vertices, std::vector<Texture> textures) :
            mVertices(std::move(vertices)),
            mTextures(std::move(textures)) {}

    virtual ~IMesh() {
        glDeleteVertexArrays(1, &mVAO);

        for (auto& texture: mTextures) {
            glDeleteTextures(1, &texture.id);

        }
    }

    virtual void setup() = 0;

    virtual void draw() = 0;

protected:
    GLuint mVAO{};
    GLuint mVBO{};
    // mesh Data
    std::vector<float> mVertices;
    std::vector<Texture> mTextures;
};
