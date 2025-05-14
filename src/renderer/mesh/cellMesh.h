#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "IMesh.hpp"
#include "texture.h"

class CellMesh final : public IMesh {
public:
    explicit CellMesh(std::vector<float>& vertices, std::vector<Texture>& textures);

    // initializes all the buffer objects/arrays
    void setup() override;

    void setupInstancing(std::vector<glm::mat4>& modelMatrices);

    // render the mesh
    void render() override;

private:
    std::vector<glm::mat4> mModelMatrices;
    GLuint mIBO{};
};