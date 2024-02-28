#pragma once

#include <vector>
#include <string>
#include "IMesh.hpp"

class SkyboxMesh : public IMesh {
public:
    SkyboxMesh(std::vector<float>& vertices, std::vector<Texture>& textures);

private:
    void setupImpl() override;

    // render the mesh
    void renderImpl() override;

};


