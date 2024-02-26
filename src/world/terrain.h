#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "cube.h"

class Terrain {
public:
    Terrain();

    void build(glm::mat4 view, glm::mat4 projection);

private:
    std::unique_ptr<Cube> m_cube;
};
