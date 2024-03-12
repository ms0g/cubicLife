#pragma once

#include <vector>
#include <string>
#include "IMesh.hpp"
#include "texture.h"

class SkyboxMesh : public IMesh {
public:
    SkyboxMesh(std::vector<float>& vertices, std::vector<Texture>& textures);

    void setup() override;

    // render the mesh
    void render() override;

private:
    std::vector<Texture> m_textures;
};


