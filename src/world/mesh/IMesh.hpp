#pragma once

#include <vector>
#include "texture.h"

class IMesh {
public:
    IMesh(std::vector<float>& vertices, std::vector<Texture> textures) :
            mVertices(std::move(vertices)),
            mTextures(std::move(textures)) {}

    virtual ~IMesh() = default;

    virtual void setup() = 0;

    virtual void render() = 0;

protected:
    unsigned int mVAO{};
    unsigned int mVBO{};
    // mesh Data
    std::vector<float> mVertices;
    std::vector<Texture> mTextures;
};
