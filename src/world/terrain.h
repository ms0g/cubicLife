#pragma once

#include <vector>
#include "glm/glm.hpp"

class Cube;
class Terrain {
public:
    Terrain();

    ~Terrain();

    void build(glm::mat4 view, glm::mat4 modelMat, glm::mat4 projection);

private:
    std::unique_ptr<Cube> mCube;
};
