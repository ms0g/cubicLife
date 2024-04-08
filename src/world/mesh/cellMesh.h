#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "IMesh.hpp"
#include "texture.h"

class CellMesh : public IMesh {
public:
    explicit CellMesh(std::vector<float>& vertices);

    // initializes all the buffer objects/arrays
    void setup() override;

    // render the mesh
    void render() override;
};