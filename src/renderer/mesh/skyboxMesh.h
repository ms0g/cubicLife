#pragma once

#include <vector>
#include "IMesh.hpp"
#include "texture.h"

class SkyboxMesh final : public IMesh {
public:
    SkyboxMesh(std::vector<float>& vertices, std::vector<Texture>& textures);

    void setup() override;

    // render the mesh
    void render() override;
};


