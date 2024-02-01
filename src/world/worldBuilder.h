#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "cube.h"

class WorldBuilder {
public:
    WorldBuilder();

    void build(glm::mat4 view, glm::mat4 projection);

private:
    Cube m_cube;
    std::vector<glm::vec3> cubePositions;

};
