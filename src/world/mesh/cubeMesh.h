#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "IMesh.hpp"

class CubeMesh : public IMesh {
public:
    CubeMesh(std::vector<float>& vertices, std::vector<Texture>& textures, std::vector<glm::mat4>& modelMatrices);

    void setupInstancing();

private:
    // initializes all the buffer objects/arrays
    void setupImpl() override;

    // render the mesh
    void renderImpl() override;

    std::vector<glm::mat4> m_modelMatrices;

    unsigned int m_instanceVBO{};


};