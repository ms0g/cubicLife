#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "IMesh.hpp"
#include "texture.h"

class CubeMesh : public IMesh {
public:
    CubeMesh(std::vector<float>& vertices, std::vector<Texture>& textures, std::vector<glm::mat4>& modelMatrices);

    // initializes all the buffer objects/arrays
    void setup() override;

    void setupInstancing();

    // render the mesh
    void render() override;

private:
    std::vector<glm::mat4> mModelMatrices;
    std::vector<Texture> mTextures;
    unsigned int mInstanceVbo{};


};