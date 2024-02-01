#pragma once

#include "glm/glm.hpp"
#include "cube.h"

class WorldBuilder {
public:
    void build(glm::mat4 view, glm::mat4 projection);
private:
    Cube m_cube;

};
